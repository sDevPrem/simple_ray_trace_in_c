#include <SDL2/SDL.h>
#include <math.h>
#include "circle_utils.h"

#define WIDTH 900
#define HEIGHT 600
#define COLOR_WHITE 0xffffffff

void waitWindow();

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Raytracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Surface* surface = SDL_GetWindowSurface(window);

    struct Circle circle = {200,200,100};
    fillCircle(surface,circle, COLOR_WHITE);

    SDL_UpdateWindowSurface(window);

    int simulation_running = 1;
    SDL_Event event;

    while(simulation_running) {
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                simulation_running = 0;
            } else if(event.type == SDL_MOUSEMOTION && event.motion.state != 0) {
                circle.x = event.motion.x;
                circle.y = event.motion.y;
            }
        }
        fillCircle(surface,circle, COLOR_WHITE);
        SDL_UpdateWindowSurface(window);
        SDL_Delay(10);
    }

    // waitWindow();
}

void waitWindow() {
    int quit = 0;
    SDL_Event e;
    while (quit != 1)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = 1;
            }
        }
    }
}
