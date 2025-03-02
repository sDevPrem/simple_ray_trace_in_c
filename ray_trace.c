#include <SDL2/SDL.h>
#include <math.h>

#define WIDTH 900
#define HEIGHT 600
#define COLOR_WHITE 0xffffffff

struct Circle {
    double x;
    double y;
    double r;
};

void waitWindow();
void fillCircle(SDL_Surface* surface, struct Circle circle, Uint32 color);

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Raytracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Surface* surface = SDL_GetWindowSurface(window);

    struct Circle circle = {200,200,100};
    fillCircle(surface,circle, COLOR_WHITE);

    SDL_UpdateWindowSurface(window);

    waitWindow();
}

void fillCircle(SDL_Surface* surface, struct Circle circle, Uint32 color) {
    double startX = circle.x - circle.r;
    double startY = circle.y - circle.r;

    double endX = circle.x + circle.r;
    double endY = circle.y + circle.r;

    double radiusSquared = pow(circle.r,2);
    //                (x,y)
    //                  *
    //                  **
    //                  * *
    //                  *  *
    //(y - circle.y)    *   * (radius)
    //                  *    *
    //                  *     *
    //                  *      *
    //                  *       *
    //                  **********(circle.x, circle.y)
    //                 (x - circle.x)

    for(double x = startX; x <= endX; x++) {
        for(double y = startY; y <= endY; y++) {
            double width = x - circle.x;
            double height = y - circle.y;

            double distanceSquared = pow(width,2) + pow(height,2);

            if(distanceSquared <= radiusSquared) {
                SDL_Rect pixel = (SDL_Rect) {x,y,1,1};
                SDL_FillRect(surface,&pixel,color);
            }
            
        }
    }
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
