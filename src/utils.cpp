#include <SDL2/SDL.h>
#include <map>
#include <fstream>
#include <vector>
#include "models.hpp"


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

std::map<std::string, std::string> decodeTextures(std::string name) {
    std::map<std::string, std::string> map;
    std::ifstream texturesFile("../doc/" + name, std::ios::in);
    std::string code, fileName;

    while (getline(texturesFile, code, ' ')) {
        getline(texturesFile, fileName);
        map[code] = fileName;
    }

    return map;
}
