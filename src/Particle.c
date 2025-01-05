#include "Particle.h"
#include "globals.h" 
#include <math.h>

void Particle_init(Particle *particle, float x, float y) 
{
    particle->x = x;
    particle->y = y;
    particle->m_particle.h = PARTICLE_HEIGHT;
    particle->m_particle.w = PARTICLE_WIDTH;

    float min_speed = 150.0f;
    float max_speed = 200.0f;

    float angle = ((float)(rand() % 360) * M_PI) / 180.0f;

    float speed = min_speed + ((float)rand() / RAND_MAX) * (max_speed - min_speed);
    particle->vx = speed * cos(angle);
    particle->vy = speed * sin(angle);

    particle->lifetime = 2.0f;

    particle->m_particle.x = (int)particle->x;
    particle->m_particle.y = (int)particle->y;
}

void Particle_move(Particle *particle, bool reverse) 
{
    const float FRAME_TIME = 1.0f / 60.0f;

    particle->x += reverse ? -particle->vx * FRAME_TIME : particle->vx * FRAME_TIME;
    particle->y += particle->vy * FRAME_TIME;

    particle->vy += GRAVITY * FRAME_TIME;

    // particle->vx *= (1.0f - DECELERATION * FRAME_TIME);
    // particle->vy *= (1.0f - DECELERATION * FRAME_TIME);

    particle->lifetime -= FRAME_TIME;

    if (particle->x < 0 || particle->x > SCREEN_WIDTH) 
    {
        particle->vx = -particle->vx * BOUNCE_FACTOR;
    }
    if (particle->y < 0 || particle->y > SCREEN_HEIGHT) 
    {
        particle->vy = -particle->vy * BOUNCE_FACTOR;
    }    

    particle->m_particle.x = ceil(particle->x);
    particle->m_particle.y = ceil(particle->y);
}

void Particle_render(Particle *particle)
{
    SDL_RenderFillRect(globals.g_renderer, &particle->m_particle);
}
