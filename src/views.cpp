#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "constants.hpp"
#include "models.hpp"
#include "views.hpp"
using namespace Views;


Map::Map(SDL_Window *window, SDL_Renderer *renderer) {
    this->window = window;
    this->renderer = renderer;
}

void Map::initializeRoom(Models::Room &room) {

    std::string code;

    code = Entities::block.codeChar;
    for (int i = 0; i < room.blocks.size(); i++) {
        room.blocks[i].texture = IMG_LoadTexture(renderer, ("../assets/" + Entities::block.textureFileName).c_str());
        SDL_QueryTexture(room.blocks[i].texture, nullptr, nullptr, &room.blocks[i].rect.w, &room.blocks[i].rect.h);
    }

    code = Entities::door.codeChar;
    for (int i = 0; i < room.doors.size(); i++) {
        room.doors[i].texture = IMG_LoadTexture(renderer, ("../assets/" + Entities::door.textureFileName).c_str());
        SDL_QueryTexture(room.doors[i].texture, nullptr, nullptr, &room.doors[i].rect.w, &room.doors[i].rect.h);
    }

    code = Entities::metroid.codeChar;
    for (int i = 0; i < room.metroids.size(); i++) {
        room.metroids[i].texture = IMG_LoadTexture(renderer, ("../assets/" + Entities::metroid.textureFileName).c_str());
        SDL_QueryTexture(room.metroids[i].texture, nullptr, nullptr, &room.metroids[i].rect.w, &room.metroids[i].rect.h);
    }
}

void Map::render(Models::Room &room) {

    // render all blocks
    for (int i = 0; i < room.blocks.size(); i++) {
        SDL_RenderCopy(renderer, room.blocks[i].texture, nullptr, &room.blocks[i].rect);
    }

    // render all doors
    for (int i = 0; i < room.doors.size(); i++) {
        SDL_RenderCopy(renderer, room.doors[i].texture, nullptr, &room.doors[i].rect);
    }

    // render all metroids
    for (int i = 0; i < room.metroids.size(); i++) {
        SDL_RenderCopy(renderer, room.metroids[i].texture, nullptr, &room.metroids[i].rect);
    }
}

void Map::destroyTextures(Models::Room &room) {
    for (int i = 0; i < room.blocks.size(); SDL_DestroyTexture(room.blocks[i++].texture));
    for (int i = 0; i < room.doors.size(); SDL_DestroyTexture(room.doors[i++].texture));
}

Samus::Samus(SDL_Window *window, SDL_Renderer *renderer) {
    this->window = window;
    this->renderer = renderer;
}

void Samus::loadTexture(Models::Samus &samus) {
    samus.texture = IMG_LoadTexture(renderer, ("../assets/" + Entities::samus.textureFileName).c_str());
    SDL_QueryTexture(samus.texture, nullptr, nullptr, &samus.rect.w, &samus.rect.h);
}

void Samus::render(Models::Samus &samus) {
    SDL_RenderCopy(renderer, samus.texture, nullptr, &samus.rect);
}

std::string Samus::processCommand() {

    // update keyboard state
    SDL_PumpEvents();

    // return command based on pressed key
    if (state[SDL_SCANCODE_SPACE]) return Commands::jump;
    if (state[SDL_SCANCODE_UP]) return Commands::lookUp;
    if (state[SDL_SCANCODE_DOWN]) return Commands::morph;
    if (state[SDL_SCANCODE_LEFT]) return Commands::moveLeft;
    if (state[SDL_SCANCODE_RIGHT]) return Commands::moveRight;

    // no supported key pressed: return nothing
    return "";
}

Shots::Shots(SDL_Window *window, SDL_Renderer *renderer) {
    this->window = window;
    this->renderer = renderer;
}

void Shots::loadTexture(Models::Shot &shot) {
    shot.texture = IMG_LoadTexture(renderer, ("../assets/" + Entities::shot.textureFileName).c_str());
    SDL_QueryTexture(shot.texture, nullptr, nullptr, &shot.rect.w, &shot.rect.h);
}

void Shots::render(std::vector<Models::Shot> &shots) {
    for (int i = 0; i < shots.size(); i++) {
        SDL_RenderCopy(renderer, shots[i].texture, nullptr, &shots[i].rect);
    }
}

std::string Shots::processCommand() {
    SDL_PumpEvents();

    if (state[SDL_SCANCODE_1]) return Commands::shot;

    return "";
}
