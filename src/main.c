#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdbool.h>
#include "globals.h"
#include "Paddle.h"
#include "Ball.h"
#include "Texture.h"
#include "drawing.h"

const int BUFFER = 2 + 1;

// Initialize SDL
bool init();
// Loads media
bool load_media();
// Frees media and shuts down SDL
void close();
// Loop handler
void loop_handler();

// Main loop flag
bool quit = false;

// Set text color as black
SDL_Color text_color = {0, 0, 0, 255};

// The player's paddle
Paddle paddle1;
Paddle paddle2;

// Pong ball
Ball ball;

// Score texture
Texture text_player1_score_texture;
Texture text_player2_score_texture;

int score1 = 0;
int score2 = 0;
char text_score1[BUFFER];
char text_score2[BUFFER];

#define RESPAWN_DELAY 1000 

Uint32 ball_respawn_time = 0;

void loop_handler()
{
    SDL_Event e;

    // Handle events on queue
    while (SDL_PollEvent(&e) != 0)
    {
        // User requests quit
        if (e.type == SDL_QUIT)
        {
            quit = true;
        }

        // Handle input for the paddles
        Paddle_handle_event(&paddle1, &e, SDLK_DOWN, SDLK_UP);
        Paddle_handle_event(&paddle2, &e, SDLK_s, SDLK_z);
    }

    // Move the paddles
    Paddle_move(&paddle1);
    Paddle_move(&paddle2);

    // Clear screen with background color
    SDL_SetRenderDrawColor(globals.g_renderer, 250, 243, 224, 0xFF);
    SDL_RenderClear(globals.g_renderer);

    // Move the ball and determine scorer
    if (!ball.m_respawn_state)
    {
        int scorer = Ball_move(&ball, &paddle1, &paddle2);
        switch (scorer)
        {
            case 0: // Ball still in play
                break;
            case 1: // Player 1 scored
                Ball_init_particles(&ball);
                score1++;
                ball.m_respawn_state = true;
                ball_respawn_time = SDL_GetTicks() + RESPAWN_DELAY;
                break;
            case 2: // Player 2 scored
                Ball_init_particles(&ball);
                score2++;
                ball.m_respawn_state = true;
                ball_respawn_time = SDL_GetTicks() + RESPAWN_DELAY;
                break;
        }
    }
    else if (SDL_GetTicks() > ball_respawn_time)
    {
        Ball_free(&ball);
        Ball_spawn(&ball, (score1 > score2));
        ball.m_respawn_state = false;
    }
    else if (ball.m_respawn_state)
    {
        Ball_render_particles(&ball, (score1 < score2));
    }

    // Render paddles
    SDL_SetRenderDrawColor(globals.g_renderer, 0x00, 0x00, 0x00, 0xFF);
    Paddle_render(&paddle1);
    Paddle_render(&paddle2);

    // Render the ball
    if (!ball.m_respawn_state) Ball_render(&ball);

    // Render the borders
    SDL_Rect top_border = {.x = 0, .y = 0, .h = BORDER_HEIGHT, .w = SCREEN_WIDTH};
    SDL_Rect bottom_border = {.x = 0, .y = SCREEN_HEIGHT - BORDER_HEIGHT, .h = BORDER_HEIGHT, .w = SCREEN_WIDTH};
    SDL_RenderFillRect(globals.g_renderer, &top_border);
    SDL_RenderFillRect(globals.g_renderer, &bottom_border);

    // Render the dotted vertical line
    draw_thick_dotted_Vline(globals.g_renderer, (SCREEN_WIDTH / 2) - 5, 0, SCREEN_HEIGHT, 25, 10, 35);

    // Render the scores
    snprintf(text_score1, sizeof(text_score1), "%d", score1);
    snprintf(text_score2, sizeof(text_score2), "%d", score2);
    Texture_load_from_rendered_text(&text_player1_score_texture, globals.g_font, text_score1, text_color);
    Texture_render(&text_player1_score_texture, (SCREEN_WIDTH / 2) - text_player1_score_texture.m_width - 10, BORDER_HEIGHT - 5, NULL);
    Texture_load_from_rendered_text(&text_player2_score_texture, globals.g_font, text_score2, text_color);
    Texture_render(&text_player2_score_texture, (SCREEN_WIDTH / 2) + 8, BORDER_HEIGHT - 5, NULL);

    // Update the screen
    SDL_RenderPresent(globals.g_renderer);
}

int main(int argc, char *args[])
{
    if (!init())
    {
        SDL_LogError(SDL_LOG_PRIORITY_ERROR, "Failed to initialize: %s", SDL_GetError());
    }
    else
    {
        // Initialize the two player paddles and the ball
        Paddle_init(&paddle1, 20, (SCREEN_HEIGHT - PADDLE_HEIGHT) / 2);
        Paddle_init(&paddle2, SCREEN_WIDTH - PADDLE_WIDTH - 20, (SCREEN_HEIGHT - PADDLE_HEIGHT) / 2);
        Ball_init(&ball);

        if (!load_media())
        {
            SDL_LogError(SDL_LOG_PRIORITY_ERROR, "Failed to load media: %s", SDL_GetError());
        }
        else
        {
            // while application is running
            while (!quit)
            {
                loop_handler();
            }
        }
    }

    // Free resources and close SDL
    close();

    return 0;
}

bool init()
{
    // Initialize flag
    bool success = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_PRIORITY_ERROR, "SDL could not initialize: %s", SDL_GetError());
        success = false;
    }
    else
    {
        // Create window
        globals.g_window = SDL_CreateWindow("Pong Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (globals.g_window == NULL)
        {
            SDL_LogError(SDL_LOG_PRIORITY_ERROR, "Window could not be created: %s", SDL_GetError());
            success = false;
        }
        else
        {
            // Create renderer for window
            globals.g_renderer = SDL_CreateRenderer(globals.g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (globals.g_renderer == NULL)
            {
                SDL_LogError(SDL_LOG_PRIORITY_ERROR, "Renderer could not be created: %s", SDL_GetError());
                success = false;
            }
            else
            {
                // Initialize renderer color
                SDL_SetRenderDrawColor(globals.g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // Initialize SDL_mixer
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                {
                    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_mixer could not initialize: %s", Mix_GetError());
                }

                // Initialize SDL_ttf
                if (TTF_Init() == -1)
                {
                    SDL_LogError(SDL_LOG_PRIORITY_ERROR, "SDL_ttf could not initialize: %s", TTF_GetError());
                }
            }
        }
    }

    return success;
}

bool load_media()
{
    // Initialize flag
    bool success = true;

    // Open the font
    globals.g_font = TTF_OpenFont("./res/retro_font.ttf", 40);
    if (globals.g_font == NULL)
    {
        SDL_LogError(SDL_LOG_PRIORITY_ERROR, "Failed to load lazy font: %s", TTF_GetError());
        success = false;
    }

    return success;
}

void close()
{
    // Free texture
    Texture_free(&text_player1_score_texture);
    Texture_free(&text_player2_score_texture);

    // Free global
    TTF_CloseFont(globals.g_font);
    globals.g_font = NULL;

    // Destroy window
    SDL_DestroyWindow(globals.g_window);
    globals.g_window = NULL;
    SDL_DestroyRenderer(globals.g_renderer);
    globals.g_renderer = NULL;

    // Quit SDL subsystems
    TTF_Quit();
    SDL_Quit();
}

