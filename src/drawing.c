#include "drawing.h"

void draw_thick_dotted_Vline(SDL_Renderer *renderer, int x1, int y1, int length, int dot_size, int thickness, int spacing)
{
    SDL_Rect rect_temp;
    rect_temp.x = x1;
    rect_temp.w = thickness;
    rect_temp.h = dot_size;
    for (int i = y1; i < length; )
    {
        rect_temp.y = i;
        SDL_RenderFillRect(renderer, &rect_temp);
        i += spacing;
    }
}
