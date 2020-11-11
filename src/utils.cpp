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

Models::Room loadRoom(std::string name) {
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

        // char belongs to the line that defines room size: ignore
        if ((c >= '0' && c <= '9') || c == 'x' || c == '\n') {
            continue;
        }

        // reached room width: go to next line
        if (x >= std::stoi(width)) {
            x = 0; y += 20;
        }

        // entity is a block: create block and add it to room
        if (c == Entities::block.codeChar) {
            Models::Block block(x, y);
            room.blocks.push_back(block);

        // entity is door: create door and add it to room
        } else if (c == Entities::door.codeChar) {
            Models::Door door(x, y);
            room.doors.push_back(door);

        // entity is metroid: create metroid and add it to room
        } else if (c == Entities::metroid.codeChar) {
            Models::Metroid metroid(x, y);
            room.metroids.push_back(metroid);

        // entity is morphing ball: create morphing ball and add it to room
        } else if (c == Entities::morphingball.codeChar) {
            room.morphingball = new Models::MorphingBall(x, y);

        // entity is motherbrain: create motherbrain and add it to room
        } else if (c == Entities::motherbrain.codeChar) {
            room.motherbrain = new Models::MotherBrain(x, y);
        }

        // increase current position
        x += 20;
    }

    return room;
}
