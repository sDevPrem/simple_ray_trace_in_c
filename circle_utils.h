#ifndef CIRCLE_UTILS_H
#define CIRCLE_UTILS_H

#include <SDL2/SDL.h>

typedef struct Circle {
    double x;
    double y;
    double r;
} Circle;

void fillCircle(SDL_Surface* surface, struct Circle circle, Uint32 color);

#endif // CIRCLE_UTILS_H