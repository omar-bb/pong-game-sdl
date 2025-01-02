#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#define PI 3.14159265359f

#define DEG2RAD(_d) ((_d) * (PI / 180.0f))
#define RAD2DEG(_d) ((_d) * (180.0f / PI))

#define min(_a, _b) ({ __typeof__(_a) __a = (_a), __b = (_b); __a < __b ? __a : __b; })
#define max(_a, _b) ({ __typeof__(_a) __a = (_a), __b = (_b); __a > __b ? __a : __b; })
#define clamp(_x, _mi, _ma) (min(max(_x, _mi), _ma))

// Checks for collision
bool check_collision(SDL_Rect a, SDL_Rect b);

#endif
