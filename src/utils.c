#include "utils.h"

bool check_collision(SDL_Rect a, SDL_Rect b)
{
    // The sides of the rectangles
    int left_a, left_b;
    int right_a, right_b;
    int top_a, top_b;
    int bottom_a, bottom_b;

    // Calculate the sides of rect A
    left_a = a.x;
    right_a = a.x + a.w;
    top_a = a.y;
    bottom_a = a.y + a.h;

    // Calculate the sides of rect B
    left_b = b.x;
    right_b = b.x + b.w;
    top_b = b.y;
    bottom_b = b.y + b.h;

    if (bottom_a <= top_b)
        return false;
    if (top_a >= bottom_b)
        return false;
    if (right_a <= left_b)
        return false;
    if (left_a >= right_b)
        return false;

    // If none of the sides from A are outside B
    return true;
}