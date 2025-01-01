#include "Ball.h"
#include "utils.h"
#include "globals.h"
#include <math.h>

// Initialize the ball
void Ball_init(Ball *ball, float x, float y)
{
    // Initialize the ball's position and dimensions
    ball->m_pos_x = x;
    ball->m_pos_y = y;
    ball->m_ball.h = BALL_HEIGHT;
    ball->m_ball.w = BALL_WIDTH;
    
    ball->m_ball.x = (int)ball->m_pos_x;
    ball->m_ball.y = (int)ball->m_pos_y;

    // Initialize the ball's velocity and pos
    ball->m_vel_x = 5.0f;
    ball->m_vel_y = 5.0f;
}


void Ball_move(Ball *ball, Paddle *paddle)
{
    // Move the ball left or right
    ball->m_pos_x += ball->m_vel_x;
    ball->m_pos_y += ball->m_vel_y;

    // Check for collision with the paddle
    if (check_collision(paddle->m_paddle, ball->m_ball))
    {
        // Push the ball out of the paddle to avoid repeated collisions
        ball->m_pos_x = paddle->m_paddle.x + paddle->m_paddle.w;

        // Calculate paddle and ball centers
        float paddle_center = paddle->m_paddle.y + (PADDLE_HEIGHT / 2.0f);
        float ball_center = ball->m_pos_y + (BALL_HEIGHT / 2.0f);
        float d = paddle_center - ball_center;

        // Normalize the distance
        float norm_d = d / 30.0f;

        // Clamp normalized distance
        if (norm_d > 1.0f) norm_d = 1.0f;
        if (norm_d < -1.0f) norm_d = -1.0f;

        // Calculate bounce angle
        float bounce_ang = norm_d * MAX_BOUNCE_ANGLE;

        // New velocity components
        float new_vel_x = 5.0f * cos(DEG2RAD(bounce_ang));
        float new_vel_y = 5.0f * -sin(DEG2RAD(bounce_ang));

        // Update velocities
        ball->m_vel_x = new_vel_x;
        ball->m_vel_y = new_vel_y;

        SDL_Log("Collision Detected");
        SDL_Log("Normalized Distance: %.2f, Bounce Angle: %.2f", norm_d, bounce_ang);
        SDL_Log("New Velocities -> X: %.2f, Y: %.2f", ball->m_vel_x, ball->m_vel_y); 
    }

    // Check collision with the left wall
    if (ball->m_pos_x < 0) 
    {
        ball->m_pos_x = 0;
        ball->m_vel_x *= -1;
    }
    // Check collision with the right wall
    else if (ball->m_pos_x + BALL_WIDTH > SCREEN_WIDTH)
    {
        ball->m_pos_x = SCREEN_WIDTH - BALL_WIDTH;
        ball->m_vel_x *= -1;
    }

    // Check collision with the top wall
    if (ball->m_pos_y < BORDER_HEIGHT) 
    {
        ball->m_pos_y = BORDER_HEIGHT;
        ball->m_vel_y *= -1;
    }
    // Check collision with the bottom wall
    else if (ball->m_pos_y + BALL_HEIGHT > SCREEN_HEIGHT - BORDER_HEIGHT)
    {
        ball->m_pos_y = SCREEN_HEIGHT - BORDER_HEIGHT - BALL_HEIGHT;
        ball->m_vel_y *= -1;
    }

    ball->m_ball.x = (int)ball->m_pos_x;
    ball->m_ball.y = (int)ball->m_pos_y;
}

// Render the ball
void Ball_render(Ball *ball)
{
    SDL_RenderFillRect(globals.g_renderer, &ball->m_ball);
}