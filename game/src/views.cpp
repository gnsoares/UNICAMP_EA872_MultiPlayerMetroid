#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "constants.hpp"
#include "models.hpp"
#include "views.hpp"
using namespace Views;


/* -=-=-=-=-=-=-=-=-=-=-=-=-  MAP  IMPLEMENTATION  -=-=-=-=-=-=-=-=-=-=-=-=- */
Map::Map(SDL_Window *window, SDL_Renderer *renderer) {
    this->window = window;
    this->renderer = renderer;
}

void Map::initializeRoom(Models::Room &room) {

    std::string code;

    // load all block textures
    code = EntitiesConstants::block.codeChar;
    for (int i = 0; i < room.blocks.size(); i++) {
        room.blocks[i].texture = IMG_LoadTexture(renderer, ("../assets/" + EntitiesConstants::block.textureFileName).c_str());
        SDL_QueryTexture(room.blocks[i].texture, nullptr, nullptr, &room.blocks[i].rect.w, &room.blocks[i].rect.h);
    }

    // load all door textures
    code = EntitiesConstants::door.codeChar;
    for (int i = 0; i < room.doors.size(); i++) {
        room.doors[i].texture = IMG_LoadTexture(renderer, ("../assets/" + EntitiesConstants::door.textureFileName).c_str());
        SDL_QueryTexture(room.doors[i].texture, nullptr, nullptr, &room.doors[i].rect.w, &room.doors[i].rect.h);
    }

    // load all metroid textures
    code = EntitiesConstants::metroid.codeChar;
    for (int i = 0; i < room.metroids.size(); i++) {
        room.metroids[i].texture = IMG_LoadTexture(renderer, ("../assets/" + EntitiesConstants::metroid.textureFileName).c_str());
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

    // destroy all textures of doors and blocks
    for (int i = 0; i < room.blocks.size(); SDL_DestroyTexture(room.blocks[i++].texture));
    for (int i = 0; i < room.doors.size(); SDL_DestroyTexture(room.doors[i++].texture));
}
/* -=-=-=-=-=-=-=-=-=-=-=- END OF MAP IMPLEMENTATION -=-=-=-=-=-=-=-=-=-=-=- */


/* -=-=-=-=-=-=-=-=-=-=-=-=- SAMUS  IMPLEMENTATION -=-=-=-=-=-=-=-=-=-=-=-=- */
Samus::Samus(SDL_Window *window, SDL_Renderer *renderer) {
    this->window = window;
    this->renderer = renderer;
}

void Samus::loadTexture(Models::Samus &samus) {

    // load Samus' texture
    samus.texture = IMG_LoadTexture(renderer, ("../assets/" + EntitiesConstants::samus.textureFileName).c_str());
    SDL_QueryTexture(samus.texture, nullptr, nullptr, &samus.rect.w, &samus.rect.h);
}

void Samus::render(Models::Samus &samus) {

    // render Samus
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
/* -=-=-=-=-=-=-=-=-=-=-  END OF SAMUS IMPLEMENTATION  -=-=-=-=-=-=-=-=-=-=- */


/* -=-=-=-=-=-=-=-=-=-=-=-=- SHOTS  IMPLEMENTATION -=-=-=-=-=-=-=-=-=-=-=-=- */
Shots::Shots(SDL_Window *window, SDL_Renderer *renderer) {
    this->window = window;
    this->renderer = renderer;
}

void Shots::loadTexture(Models::Shot &shot) {

    // load shot texture
    shot.texture = IMG_LoadTexture(renderer, ("../assets/" + EntitiesConstants::shot.textureFileName).c_str());
    SDL_QueryTexture(shot.texture, nullptr, nullptr, &shot.rect.w, &shot.rect.h);
}

void Shots::render(std::vector<Models::Shot> &shots) {

    // render all shots
    for (int i = 0; i < shots.size(); i++) {
        SDL_RenderCopy(renderer, shots[i].texture, nullptr, &shots[i].rect);
    }
}

std::string Shots::processCommand() {
    // update keyboard state
    SDL_PumpEvents();

    // return command based on pressed key
    if (state[SDL_SCANCODE_1]) return Commands::shot;

    // no supported key pressed: return nothing
    return "";
}
/* -=-=-=-=-=-=-=-=-=-=-  END OF SHOTS IMPLEMENTATION  -=-=-=-=-=-=-=-=-=-=- */
