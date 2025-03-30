#include <SDL2/SDL.h>
#include <math.h>
#include "circle_utils.h"

#define WIDTH 900
#define HEIGHT 600
#define COLOR_WHITE 0xffffffff
#define COLOR_BLACK 0x000000
#define RAYS_NUMBER 100

struct Ray
{
    double x_start, y_start;
    double angle;
};


void waitWindow();
void generateRays(Circle circle, struct Ray rays[RAYS_NUMBER]);
void fillRays(SDL_Surface* surface, struct Ray rays[RAYS_NUMBER], Uint32 rayColor);


int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Raytracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Surface* surface = SDL_GetWindowSurface(window);

    SDL_Rect eraseRect = {0, 0, WIDTH, HEIGHT};
    Circle circle = {200,200,100};
    Circle shadowCircle = {700,300, 140};
    struct Ray rays[RAYS_NUMBER];
    
    fillCircle(surface,circle, COLOR_WHITE);
    fillCircle(surface,shadowCircle, COLOR_WHITE);
    generateRays(circle,rays);
    fillRays(surface,rays,COLOR_WHITE);
    SDL_UpdateWindowSurface(window);


    int simulation_running = 1;
    SDL_Event event;

    while(simulation_running) {
        int newX, newY = 0;
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                simulation_running = 0;
            } else if(event.type == SDL_MOUSEMOTION && event.motion.state != 0) {
                newX = event.motion.x;
                newY = event.motion.y;
            }
        }

        if(newX != 0 && newY != 0 && circle.x != newX && circle.y != newY) {
            circle.x = newX;
            circle.y = newY;

            SDL_FillRect(surface,&eraseRect,COLOR_BLACK);

            fillCircle(surface,circle, COLOR_WHITE);
            fillCircle(surface,shadowCircle, COLOR_WHITE);

            generateRays(circle,rays);
            fillRays(surface,rays,COLOR_WHITE);

            SDL_UpdateWindowSurface(window);
            SDL_Delay(10);
        }
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

void generateRays(Circle circle, struct Ray rays[RAYS_NUMBER])
{
    for(int i = 0; i <= RAYS_NUMBER; i++) {
        double angle = ((double) i/RAYS_NUMBER) * 2 * M_PI;
        struct Ray ray = { circle.x, circle.y, angle };
        rays[i] = ray;
    }
    
    
}

void fillRays(SDL_Surface* surface, struct Ray rays[RAYS_NUMBER], Uint32 rayColor) {
    for(int i = 0; i <= RAYS_NUMBER; i++) { 
        struct Ray ray = rays[i];
        double x_draw = ray.x_start;
        double y_draw = ray.y_start;
        int endOfTheScreen = 0;
        int objectHit = 0;
        double step = 0.3;

        while(!endOfTheScreen && !objectHit) {
            x_draw += step * cos(ray.angle);
            y_draw += step * sin(ray.angle);

            SDL_Rect pixel = (SDL_Rect) {x_draw,y_draw,1,1};
            SDL_FillRect(surface,&pixel,rayColor);

            if(x_draw < 0 || x_draw > WIDTH || y_draw < 0  || y_draw > HEIGHT) {
                endOfTheScreen = 1;
            }
            step += 0.1;
        }
    }
}
