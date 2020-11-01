#include <SDL2/SDL.h>

bool checkCollision(SDL_Rect rect1, SDL_Rect rect2) {

    // check overlap in x
    bool xOverlap = 
        (rect1.x >= rect2.x && rect1.x < rect2.x + rect2.w)
     || (rect2.x >= rect1.x && rect2.x < rect1.x + rect1.w);

    // check overlap in y
    bool yOverlap = 
        (rect1.y >= rect2.y && rect1.y < rect2.y + rect2.h)
     || (rect2.y >= rect1.y && rect2.y < rect1.y + rect1.h);

    // rectangles overlap in x and y: they are colliding
    return xOverlap && yOverlap;
}
