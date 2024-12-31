#ifndef PADDLE_H
#define PADDLE_H

#include <SDL2/SDL.h>

#define PADDLE_WIDTH 10
#define PADDLE_HEIGHT 60

#define PADDLE_VEL 16

// Player's paddle
typedef struct {
    SDL_Rect m_paddle;
    int m_vel;
} Paddle;

// Initialize paddle
void Paddle_init(Paddle *paddle, int x, int y);
// Move paddle
void Paddle_move(Paddle *paddle);
// Handle event
void Paddle_handle_event(Paddle *paddle, SDL_Event *e);
// Render
void Paddle_render(Paddle *paddle);

#endif
