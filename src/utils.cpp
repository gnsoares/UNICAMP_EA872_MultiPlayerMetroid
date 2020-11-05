#include <SDL2/SDL.h>
#include <cstdio>
#include <map>
#include <fstream>
#include <vector>
#include "constants.hpp"
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

Models::Room loadRoom(std::string name, std::map<std::string, std::string> textureMap) {
    int c, x = 0, y = 0;
    Models::Room room;
    std::string path = "../doc/rooms/" + name + ".room", width, height;
    FILE *roomFile = fopen(path.c_str(), "r");
    std::ifstream roomFileStream(path, std::ios::in);

    getline(roomFileStream, width, 'x');
    getline(roomFileStream, height);

    while (feof(roomFile) == 0) {
        c = getc(roomFile);
        if (x >= std::stoi(width)) {
            x = 0; y += 20;
        }
        if (c == ' ' || c == 'S') {
        } else if (c == '#') {
            Models::Block block(x, y);
            block.textureFile = textureMap["#"];
            room.blocks.push_back(block);
        } else if (c == 'D') {
            Models::Door door(x, y);
            door.textureFile = textureMap["D"];
            room.doors.push_back(door);
        } else if (c == 'X') {
            Models::Metroid metroid(x, y);
            metroid.textureFile = textureMap["X"];
            room.metroids.push_back(metroid);
        } else if (c == 'B') {
            room.morphingball = new Models::MorphingBall(x, y);
            room.morphingball->textureFile = textureMap["B"];
        } else if (c == 'M') {
            room.motherbrain = new Models::MotherBrain(x, y);
            room.motherbrain->textureFile = textureMap["M"];
        } else if (c == 'X') {
            Models::Metroid metroid(x, y);
            metroid.textureFile = textureMap["X"];
            room.metroids.push_back(metroid);
        } else {
            continue;
        }
        x += 20;
    }

    return room;
}
