#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Screen dimensions
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

// Borders dimensions
#define BORDER_H 15

#define PI 3.14159265359f
#define TAU (2.0f * PI)
#define PI_2 (PI / 2.0f)
#define PI_4 (PI / 4.0f)

#define DEG2RAD(_d) ((_d) * (PI / 180.0f))
#define RAD2DEG(_d) ((_d) * (180.0f / PI))

// Globals struct
typedef struct {
    SDL_Window *g_window;
    SDL_Renderer *g_renderer;
    TTF_Font *g_font;
} Globals;

// extern declaration of the global variables
extern Globals globals;

#endif
