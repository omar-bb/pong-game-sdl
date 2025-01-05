#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>
#include "Paddle.h"
#include <stdbool.h>
#include "Particle.h"

// Ball's dimensions macros
#define BALL_HEIGHT 10
#define BALL_WIDTH 10

// Ball's velocity macros
#define INITIAL_BALL_VELOCITY 5 
#define VELOCITY_INCREMENT 0.5
#define MAX_BALL_SPEED 12

#define MAX_BOUNCE_ANGLE 45.0f

typedef struct {
    SDL_Rect m_ball;
    float m_pos_x, m_pos_y;
    float m_vel_x, m_vel_y;
    bool m_respawn_state;
    Particle *particles[TOTAL_PARTICLES];
} Ball;

// Initialize the ball (velocity and position)
void Ball_init(Ball *ball);
// Spawn ball
void Ball_spawn(Ball *ball, bool reverse);
// Move the ball
int Ball_move(Ball *ball, Paddle *paddle1, Paddle *paddle2);
// Handle paddle collision
void Ball_handle_paddle_collision(Ball *ball, Paddle *paddle, bool reverse);
// Render ball
void Ball_render(Ball *ball);

// -- Particles

// Initialize particles
void Ball_init_particles(Ball *ball);
// Render particles from the ball
void Ball_render_particles(Ball *ball, bool reverse);
// Free particles
void Ball_free(Ball *ball);

#endif
