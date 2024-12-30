#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdbool.h>
#include "globals.h"

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
    }

}

int main(int argc, char *args[])
{
    if (!init())
    {
        SDL_LogError(SDL_LOG_PRIORITY_ERROR, "Failed to initialize: %s", SDL_GetError());
    }
    else
    {
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
    globals.g_font = TTF_OpenFont("./res/retro_font.ttf", 30);
    if (globals.g_font == NULL)
    {
        SDL_LogError(SDL_LOG_PRIORITY_ERROR, "Failed to load lazy font: %s", TTF_GetError());
        success = false;
    }

    return success;
}

void close()
{
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

