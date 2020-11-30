#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
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

std::string collideWithWall(SDL_Rect object, SDL_Rect wall, int prevX, int prevY) {

    // collided with floor
    if (object.y + object.h >= wall.y && prevY + object.h <= wall.y)
        return "floor";

    // collided with ceiling
    if (wall.y + wall.h >= object.y && wall.y + wall.h <= prevY)
        return "ceiling";

    // collided with right wall
    if (object.x + object.w >= wall.x && prevX + object.w <= wall.x)
        return "right";

    // collided with left wall
    if (wall.x + wall.w >= object.x && wall.x + wall.w <= prevX)
        return "left";

    // failed for all walls: return nothing
    return "";
}

void processMetroidCollisionWithWall(Models::Metroid &metroid, std::vector<Models::Block> blocks, int prevX, int prevY) {
    std::string collision = "";

    for (int i = 0; i < blocks.size(); i++) {
        if (checkCollision(blocks[i].rect, metroid.rect)) {

            // check which side collided
            collision = collideWithWall(metroid.rect, blocks[i].rect, prevX, prevY);

            // collided with floor
            if (collision == "floor") {

                // set feet at the top of the block
                metroid.rect.y = blocks[i].rect.y - metroid.rect.h;

                // set acceleration away from floor and set new resting position
                metroid.ay -= 5; metroid.yi -= 5;
            }

            // collided with ceiling
            else if (collision == "ceiling") {

                // set head at the bottomm of the block
                metroid.rect.y = blocks[i].rect.y + blocks[i].rect.h;

                // set acceleration away from ceiling and set new resting position
                metroid.ay += 5; metroid.yi += 5;
            }

            // collided with right wall
            else if (collision == "right") {

                // set right side at the left side of the block
                metroid.rect.x = blocks[i].rect.x - metroid.rect.w;

                // set acceleration away from wall and set new resting position
                metroid.ax -= 5; metroid.xi -= 5;
            }

            // collided with left wall
            else if (collision == "left") {

                // set left side at the right side of the block
                metroid.rect.x = blocks[i].rect.x + blocks[i].rect.w;

                // set acceleration away from wall and set new resting position
                metroid.ax += 5; metroid.xi += 5;
            }
        }
    }
}
void processMetroidCollisionWithWall(Models::Metroid &metroid, std::vector<Models::Door> doors, int prevX, int prevY) {
    std::string collision = "";

    for (int i = 0; i < doors.size(); i++) {

        // door open: ignore
        if (doors[i].isOpen)
            continue;

        if (checkCollision(doors[i].rect, metroid.rect)) {

            // check which side collided
            collision = collideWithWall(metroid.rect, doors[i].rect, prevX, prevY);

            // collided with floor
            if (collision == "floor") {

                // set feet at the top of the block
                metroid.rect.y = doors[i].rect.y - metroid.rect.h;

                // set acceleration away from floor and set new resting position
                metroid.ay -= 5; metroid.yi -= 5;
            }

            // collided with ceiling
            else if (collision == "ceiling") {

                // set head at the bottomm of the block
                metroid.rect.y = doors[i].rect.y + doors[i].rect.h;

                // set acceleration away from ceiling and set new resting position
                metroid.ay += 5; metroid.yi += 5;
            }

            // collided with right wall
            else if (collision == "right") {

                // set right side at the left side of the block
                metroid.rect.x = doors[i].rect.x - metroid.rect.w;

                // set acceleration away from wall and set new resting position
                metroid.ax -= 5; metroid.xi -= 5;
            }

            // collided with left wall
            else if (collision == "left") {

                // set left side at the right side of the block
                metroid.rect.x = doors[i].rect.x + doors[i].rect.w;

                // set acceleration away from wall and set new resting position
                metroid.ax += 5; metroid.xi += 5;
            }
        }
    }
}

void processSamusCollisionWithWall(Models::Samus &samus, std::vector<Models::Block> blocks, int prevX, int prevY) {
    std::string collision = "";

    for (int i = 0; i < blocks.size(); i++) {
        if (checkCollision(blocks[i].rect, samus.rect)) {

            // check which side collided
            collision = collideWithWall(samus.rect, blocks[i].rect, prevX, prevY);

            // collided with floor: set feet at the top of the block update Samus' state
            if (collision == "floor") {
                samus.rect.y = blocks[i].rect.y - samus.rect.h;
                samus.isJumping = samus.isFalling = false;
            }

            // collided with ceiling: set head at the bottomm of the block update Samus' state
            else if (collision == "ceiling") {
                samus.rect.y = blocks[i].rect.y + blocks[i].rect.h;
                samus.isFalling = true;
            }

            // collided with right wall: set right side at the left side of the block update Samus' state
            else if (collision == "right") {
                samus.rect.x = blocks[i].rect.x - samus.rect.w;
                samus.isFalling = true;
            }

            // collided with left wall: set left side at the right side of the block update Samus' state
            else if (collision == "left") {
                samus.rect.x = blocks[i].rect.x + blocks[i].rect.w;
                samus.isFalling = true;
            }

            // samus must enter free fall if she collides
            if (!samus.isFalling) samus.vy = 0;
        }
    }
}
void processSamusCollisionWithWall(Models::Samus &samus, std::vector<Models::Door> doors, int prevX, int prevY) {
    std::string collision = "";

    for (int i = 0; i < doors.size(); i++) {

        // door open: ignore
        if (doors[i].isOpen)
            continue;

        if (checkCollision(doors[i].rect, samus.rect)) {

            // check which side collided
            collision = collideWithWall(samus.rect, doors[i].rect, prevX, prevY);

            // collided with floor: set feet at the top of the block update Samus' state
            if (collision == "floor") {
                samus.rect.y = doors[i].rect.y - samus.rect.h;
                samus.isJumping = samus.isFalling = false;
            }

            // collided with ceiling: set head at the bottomm of the block update Samus' state
            else if (collision == "ceiling") {
                samus.rect.y = doors[i].rect.y + doors[i].rect.h;
                samus.isFalling = true;
            }

            // collided with right wall: set right side at the left side of the block update Samus' state
            else if (collision == "right") {
                samus.rect.x = doors[i].rect.x - samus.rect.w;
                samus.isFalling = true;
            }

            // collided with left wall: set left side at the right side of the block update Samus' state
            else if (collision == "left") {
                samus.rect.x = doors[i].rect.x + doors[i].rect.w;
                samus.isFalling = true;
            }

            // samus must enter free fall if she collides
            if (!samus.isFalling) samus.vy = 0;
        }
    }
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
        if (c == EntitiesConstants::block.codeChar) {
            Models::Block block(x, y);
            room.blocks.push_back(block);

        // entity is door: create door and add it to room
        } else if (c == EntitiesConstants::door.codeChar) {
            Models::Door door(x, y);
            room.doors.push_back(door);

        // entity is metroid: create metroid and add it to room
        } else if (c == EntitiesConstants::metroid.codeChar) {
            Models::Metroid metroid(x, y);
            room.metroids.push_back(metroid);

        // entity is morphing ball: create morphing ball and add it to room
        } else if (c == EntitiesConstants::morphingball.codeChar) {
            room.morphingball = new Models::MorphingBall(x, y);

        // entity is motherbrain: create motherbrain and add it to room
        } else if (c == EntitiesConstants::motherbrain.codeChar) {
            room.motherbrain = new Models::MotherBrain(x, y);
        }

        // increase current position
        x += 20;
    }

    return room;
}

SDL_Window *loadWindow() {
    SDL_Window *window;

    // create window
    window = SDL_CreateWindow(
        "Metroid Clone",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        Screen::width,
        Screen::height,
        SDL_WINDOW_SHOWN
    );

    // window creation failed: print error
    if (window == nullptr) {
        std::cout << SDL_GetError();
        SDL_Quit();
    }

    return window;
}

SDL_Renderer *loadRenderer(SDL_Window *window) {
    SDL_Renderer *renderer;

    // create renderer
    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    // renderer creation failed: print error
    if (renderer == nullptr) {
        SDL_DestroyWindow(window);
        std::cout << SDL_GetError();
        SDL_Quit();
    }

    return renderer;
}

void unloadSDL(SDL_Window *window, SDL_Renderer *renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
