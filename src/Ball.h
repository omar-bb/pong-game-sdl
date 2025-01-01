#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>
#include "Paddle.h"

// Ball's dimensions macros
#define BALL_HEIGHT 10
#define BALL_WIDTH 10

// Ball's velocity macros
#define INITIAL_BALL_VELOCITY 5 
#define VELOCITY_INCREMENT 0.5
#define MAX_BALL_SPEED 12

#define MAX_BOUNCE_ANGLE 30.0f

typedef struct {
    SDL_Rect m_ball;
    float m_pos_x, m_pos_y;
    float m_vel_x, m_vel_y;
} Ball;

// Initialize the ball (velocity and position)
void Ball_init(Ball *ball, float x, float y);
// Move the ball
void Ball_move(Ball *ball, Paddle *paddle);
// Render ball
void Ball_render(Ball *ball);

#endif
