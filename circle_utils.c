#include <SDL2/SDL.h>
#include <math.h>
#include "circle_utils.h"

int isPointInsideCircle(int x, int y, struct Circle circle);

void fillCircle(SDL_Surface* surface, struct Circle circle, Uint32 color) {
    double startX = circle.x - circle.r;
    double startY = circle.y - circle.r;

    double endX = circle.x + circle.r;
    double endY = circle.y + circle.r;

    for(double x = startX; x <= endX; x++) {
        for(double y = startY; y <= endY; y++) {

            if(isPointInsideCircle(x,y,circle)) {
                SDL_Rect pixel = (SDL_Rect) {x,y,1,1};
                SDL_FillRect(surface,&pixel,color);
            }
        }
    }
}

int isPointInsideCircle(int x, int y, struct Circle circle) {
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

    double width = x - circle.x;
    double height = y - circle.y;
    double radiusSquared = pow(circle.r,2);

    double distanceSquared = pow(width,2) + pow(height,2);

    if(distanceSquared <= radiusSquared) {
        return 1;
    }
    return 0;
}