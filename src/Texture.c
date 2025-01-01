#include "Texture.h"
#include "globals.h"

bool Texture_load_from_rendered_text(Texture *texture, TTF_Font *g_font, const char *texture_text, SDL_Color text_color)
{
    SDL_Surface *text_surface = TTF_RenderText_Solid(g_font, texture_text, text_color);

    if (text_surface == NULL)
    {
        SDL_LogError(SDL_LOG_PRIORITY_ERROR, "Unable to render text surface: %s", TTF_GetError());
    }
    else 
    {
        // Create texture from surface pixels
        texture->m_texture = SDL_CreateTextureFromSurface(globals.g_renderer, text_surface);
        if (texture->m_texture == NULL)
        {
            SDL_LogError(SDL_LOG_PRIORITY_ERROR, "Unable to create texture from rendered text: %s", SDL_GetError());
        } 
        else
        {
            // Get image dimensions
            texture->m_width = text_surface->w;
            texture->m_height = text_surface->h;
        }

        // Get rid of old surface
        SDL_FreeSurface(text_surface);
    }

    return texture->m_texture != NULL;
}

void Texture_render(Texture *texture, int x, int y, SDL_Rect *clip)
{
    if (texture == NULL)
    {
        return;
    }

    // Set rendering space and render to screen
    SDL_Rect render_quad = {x, y, texture->m_width, texture->m_height};

    // Set clip rendering dimensions
    if (clip != NULL)
    {
        render_quad.w = clip->w;
        render_quad.h = clip->h;
    }

    // Render to screen
    SDL_RenderCopy(globals.g_renderer, texture->m_texture, clip, &render_quad);
}

void Texture_free(Texture *texture)
{
    if (texture != NULL)
    {
        if (texture->m_texture)
        {
            SDL_DestroyTexture(texture->m_texture);
            texture->m_texture = NULL;
        }

        texture->m_width = 0;
        texture->m_height = 0;
    }
}
