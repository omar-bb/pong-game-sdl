#include "Paddle.h"
#include "globals.h"

void Paddle_init(Paddle *paddle, int x, int y)
{
    // Initialize paddle's default position and dimensions
    paddle->m_paddle.x = x;
    paddle->m_paddle.y = y;
    paddle->m_paddle.h = PADDLE_HEIGHT;
    paddle->m_paddle.w = PADDLE_WIDTH;
}

void Paddle_handle_event(Paddle *paddle, SDL_Event *e)
{
    // If a key was pressed
    if (e->type == SDL_KEYDOWN && e->key.repeat == 0)
    {
        // Adjust the velocity
        switch (e->key.keysym.sym)
        {
            case SDLK_UP: paddle->m_vel -= PADDLE_VEL; break;
            case SDLK_DOWN: paddle->m_vel += PADDLE_VEL; break;
        }
    }
    // If a key was released
    else if (e->type == SDL_KEYUP && e->key.repeat == 0)
    {
        // Adjust the velocity
        switch (e->key.keysym.sym)
        {
            case SDLK_UP: paddle->m_vel += PADDLE_VEL; break;
            case SDLK_DOWN: paddle->m_vel -= PADDLE_VEL; break;
        }
    }
}

void Paddle_move(Paddle *paddle)
{
    // Move the paddle left or right 
    paddle->m_paddle.y += paddle->m_vel;

    // If the paddle went too far
    if (paddle->m_paddle.y < BORDER_H)
    {
        // Move back
        paddle->m_paddle.y = BORDER_H;
    }
    else if (paddle->m_paddle.y + paddle->m_paddle.h > SCREEN_HEIGHT - BORDER_H)
    {
        paddle->m_paddle.y = SCREEN_HEIGHT - BORDER_H - paddle->m_paddle.h;
    }
}

void Paddle_render(Paddle *paddle)
{
    SDL_RenderFillRect(globals.g_renderer, &paddle->m_paddle);
}