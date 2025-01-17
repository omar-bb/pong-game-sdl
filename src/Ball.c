#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Ball.h"
#include "utils.h"
#include "globals.h"
#include <math.h>

// Initialize the ball
void Ball_init(Ball *ball)
{
    ball->m_respawn_state = false;

    // Initialize the ball dimensions
    ball->m_ball.h = BALL_HEIGHT;
    ball->m_ball.w = BALL_WIDTH;

    Ball_spawn(ball, true);
    
    ball->m_ball.x = (int)ball->m_pos_x;
    ball->m_ball.y = (int)ball->m_pos_y;
}

void Ball_spawn(Ball *ball, bool reverse)
{
    // Seed the random number generator with the current time
    srand((unsigned int)time(NULL));

    int ran_ang = rand() % 46;
    int ran_ball_pos = 50 + rand() % (430 - 50 + 1);

    // Random ball pos
    ball->m_pos_x = SCREEN_WIDTH / 2;
    ball->m_pos_y = ran_ball_pos;

    float vel_x = 3.0f * cos(DEG2RAD(ran_ang));
    float vel_y = 3.0f * -sin(DEG2RAD(ran_ang));

    ball->m_vel_x = reverse ? -vel_x : vel_x;
    ball->m_vel_y = reverse ? -vel_y : vel_y;
}

int Ball_move(Ball *ball, Paddle *paddle1, Paddle *paddle2)
{
    // Move the ball left or right
    ball->m_pos_x += ball->m_vel_x;
    ball->m_pos_y += ball->m_vel_y;

    // Check for collision with the paddles
    if (check_collision(paddle1->m_paddle, ball->m_ball))
        Ball_handle_paddle_collision(ball, paddle1, false);
    else if (check_collision(paddle2->m_paddle, ball->m_ball))
        Ball_handle_paddle_collision(ball, paddle2, true);

    // Check collision with the left wall
    if (ball->m_pos_x < 0/*&& !ball->m_respawn_state*/) 
    {
        ball->m_ball.x = (int)ball->m_pos_x;
        ball->m_ball.y = (int)ball->m_pos_y;
        return 2;
    }
    // Check collision with the right wall
    else if (ball->m_pos_x + BALL_WIDTH > SCREEN_WIDTH/* && !ball->m_respawn_state*/)
    {
        ball->m_ball.x = (int)ball->m_pos_x;
        ball->m_ball.y = (int)ball->m_pos_y;
        return 1;
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

    return 0;
}

void Ball_handle_paddle_collision(Ball *ball, Paddle *paddle, bool reverse)
{
    // Push the ball out of the paddle to avoid repeated collisions
    ball->m_pos_x = reverse ? paddle->m_paddle.x - paddle->m_paddle.w :
                              paddle->m_paddle.x + paddle->m_paddle.w;

    // Calculate paddle and ball centers
    float paddle_center = paddle->m_paddle.y + (PADDLE_HEIGHT / 2.0f);
    float ball_center = ball->m_pos_y + (BALL_HEIGHT / 2.0f);
    float d = paddle_center - ball_center;

    // Normalize the distance and clamp it
    float norm_d = clamp(d / 30.0f, -1.0f, 1.0f);

    // Calculate bounce angle
    float bounce_ang = norm_d * MAX_BOUNCE_ANGLE;

    // New velocity components
    float new_vel_x = 5.0f * cos(DEG2RAD(bounce_ang));
    float new_vel_y = 5.0f * -sin(DEG2RAD(bounce_ang));

    // Update velocities
    ball->m_vel_x = reverse ? -new_vel_x : new_vel_x;
    ball->m_vel_y = reverse ? -new_vel_y : new_vel_y;

    SDL_Log("Collision Detected");
    SDL_Log("Normalized Distance: %.2f, Bounce Angle: %.2f", norm_d, bounce_ang);
    SDL_Log("New Velocities -> X: %.2f, Y: %.2f", ball->m_vel_x, ball->m_vel_y); 
}

// Render the ball
void Ball_render(Ball *ball)
{
    SDL_RenderFillRect(globals.g_renderer, &ball->m_ball);
}