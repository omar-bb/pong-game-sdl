#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdbool.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

typedef struct {
    SDL_Texture *m_texture;
    int m_width, m_height;
} Texture;

// Create image from font string
bool Texture_load_from_rendered_text(Texture *texture, TTF_Font *g_font, const char *texture_text, SDL_Color text_color);
// Render texture
void Texture_render(Texture *texture, int x, int y, SDL_Rect *clip);
// Free texture
void Texture_free(Texture *texture);

#endif
