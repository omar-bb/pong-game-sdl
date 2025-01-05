#ifndef PARTICLE_H
#define PARTICLE_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#define PARTICLE_HEIGHT 5 
#define PARTICLE_WIDTH 5 

#define TOTAL_PARTICLES 25 

#define GRAVITY 9.8f
#define DECELERATION 0.1f 
#define BOUNCE_FACTOR 0.7f

typedef struct {
    SDL_Rect m_particle;
    float x, y;
    float vx, vy;
    float lifetime;
} Particle;

// Initialize particle's position and animation
void Particle_init(Particle *particle, float x, float y);
// Render particle
void Particle_render(Particle *particle);
// Move particle
void Particle_move(Particle *particle, bool reverse);

#endif 
