#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Screen dimensions
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define H_SCREEN_WIDTH SCREEN_WIDTH / 2
#define H_SCREEN_HEIGHT SCREEN_HEIGHT / 2

// Borders dimensions
#define BORDER_HEIGHT 15

// Globals struct
typedef struct {
    SDL_Window *g_window;
    SDL_Renderer *g_renderer;
    TTF_Font *g_font;
} Globals;

// extern declaration of the global variables
extern Globals globals;

#endif
