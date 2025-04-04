#include <SDL2/SDL.h>
#include <math.h>
#include "circle_utils.h"

#define WIDTH 1200
#define HEIGHT 600
#define COLOR_WHITE 0xffffffff
#define COLOR_BLACK 0x000000
#define RAYS_NUMBER 400
#define COLOR_RAY 0xffd43b
#define COLOR_RAY_BLUR 0xebdaa0
#define RAY_THICKNESS 1

struct Ray
{
    double x_start, y_start;
    double angle;
};


void waitWindow();
void generateRays(Circle circle, struct Ray rays[RAYS_NUMBER]);
void fillRays(SDL_Surface* surface, struct Ray rays[RAYS_NUMBER], Uint32 rayColor, Uint32 blurRayColor, struct Circle object);


int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Raytracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Surface* surface = SDL_GetWindowSurface(window);

    SDL_Rect eraseRect = {0, 0, WIDTH, HEIGHT};
    Circle circle = {200,200,40};
    Circle shadowCircle = {550,300, 140};
    struct Ray rays[RAYS_NUMBER];

    int obstacleSpeed = 1;
    
    fillCircle(surface,circle, COLOR_WHITE);
    fillCircle(surface,shadowCircle, COLOR_WHITE);
    generateRays(circle,rays);
    fillRays(surface,rays,COLOR_WHITE,COLOR_RAY_BLUR,shadowCircle);
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

        SDL_FillRect(surface,&eraseRect,COLOR_BLACK);

        generateRays(circle,rays);
        fillRays(surface,rays,COLOR_RAY,COLOR_RAY_BLUR,shadowCircle);
        fillCircle(surface,circle, COLOR_WHITE);
        fillCircle(surface,shadowCircle, COLOR_WHITE);


        SDL_UpdateWindowSurface(window);

        shadowCircle.y += obstacleSpeed;
        if(shadowCircle.y - shadowCircle.r < 0 || shadowCircle.y + shadowCircle.r > HEIGHT) {
            obstacleSpeed = -obstacleSpeed;
        }
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

void generateRays(Circle circle, struct Ray rays[RAYS_NUMBER])
{
    for(int i = 0; i <= RAYS_NUMBER; i++) {
        double angle = ((double) i/RAYS_NUMBER) * 2 * M_PI;
        struct Ray ray = { circle.x, circle.y, angle };
        rays[i] = ray;
    }
    
    
}

void fillRays(SDL_Surface* surface, struct Ray rays[RAYS_NUMBER], Uint32 rayColor, Uint32 blurRayColor, struct Circle object) {
    for(int i = 0; i <= RAYS_NUMBER; i++) { 
        struct Ray ray = rays[i];
        double x_draw = ray.x_start;
        double y_draw = ray.y_start;
        int endOfTheScreen = 0;
        int objectHit = 0;
        double step = 1;

        while(!endOfTheScreen && !objectHit) {
            double blurRayThickness = 1.5 * RAY_THICKNESS;
            SDL_Rect pixel = (SDL_Rect) {x_draw,y_draw,RAY_THICKNESS,RAY_THICKNESS};
            SDL_Rect blur_pixel = (SDL_Rect) {x_draw,y_draw,blurRayThickness,blurRayThickness};

            SDL_FillRect(surface,&blur_pixel,blurRayColor);
            SDL_FillRect(surface,&pixel,rayColor);

            x_draw += step * cos(ray.angle);
            y_draw += step * sin(ray.angle);

            if(isPointInsideCircle(x_draw,y_draw,object)) {
                objectHit = 1;
            } 
            if(x_draw < 0 || x_draw > WIDTH || y_draw < 0  || y_draw > HEIGHT) {
                endOfTheScreen = 1;
            }
            // step += 0.1;
        }
    }
}
