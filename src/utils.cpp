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

    // line until the space is the entity code
    while (getline(texturesFile, code, ' ')) {

        // line until line break is the texture file name
        getline(texturesFile, fileName);

        // register the pair entity code - texture file name
        map[code] = fileName;
    }

    return map;
}

Models::Room loadRoom(std::string name, std::map<std::string, std::string> textureMap) {
    int c, x = 0, y = 0;
    Models::Room room;
    std::string path = "../doc/rooms/" + name + ".room", width, height, code;
    FILE *roomFile = fopen(path.c_str(), "r");
    std::ifstream roomFileStream(path, std::ios::in);

    // register room's width and height
    getline(roomFileStream, width, 'x');
    getline(roomFileStream, height);

    // while end of file is not reached: read room
    while (feof(roomFile) == 0) {

        // each char is a room entity
        c = getc(roomFile);
        code = c;

        // reached room width: go to next line
        if (x >= std::stoi(width)) {
            x = 0; y += 20;
        }

        // entity is empty or samus: do nothing
        if (c == EntityCodes::empty || c == EntityCodes::samus) {
        }

        // entity is a block: create block and add it to room
        else if (c == EntityCodes::block) {
            Models::Block block(x, y, 0, 0);
            block.textureFile = textureMap[code];
            room.blocks.push_back(block);

        // entity is door: create door and add it to room
        } else if (c == EntityCodes::door) {
            Models::Door door(x, y, 0, 0);
            door.textureFile = textureMap[code];
            room.doors.push_back(door);

        // entity is metroid: create metroid and add it to room
        } else if (c == EntityCodes::metroid) {
            Models::Metroid metroid(x, y, 0, 0);
            metroid.textureFile = textureMap[code];
            room.metroids.push_back(metroid);

        // entity is morphing ball: create morphing ball and add it to room
        } else if (c == EntityCodes::morphingball) {
            room.morphingball = new Models::MorphingBall(x, y, 0, 0);
            room.morphingball->textureFile = textureMap[code];

        // entity is motherbrain: create motherbrain and add it to room
        } else if (c == EntityCodes::motherbrain) {
            room.motherbrain = new Models::MotherBrain(x, y, 0, 0);
            room.motherbrain->textureFile = textureMap[code];

        // entity is not supported: ignore
        } else {
            continue;
        }

        // increase current position
        x += 20;
    }

    return room;
}
