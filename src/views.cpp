#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "constants.hpp"
#include "models.hpp"
#include "views.hpp"
using namespace Views;


Map::Map() {
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
}

void Map::initializeRoom(Models::Room &room, Models::Samus &samus) {

    std::string code;

    code = EntityCodes::samus;
    samus.texture = IMG_LoadTexture(renderer, ("../assets/" + samus.textureFile).c_str());
    SDL_QueryTexture(samus.texture, nullptr, nullptr, &samus.rect.w, &samus.rect.h);

    code = EntityCodes::block;
    for (int i = 0; i < room.blocks.size(); i++) {
        room.blocks[i].texture = IMG_LoadTexture(renderer, ("../assets/" + room.blocks[i].textureFile).c_str());
        SDL_QueryTexture(room.blocks[i].texture, nullptr, nullptr, &room.blocks[i].rect.w, &room.blocks[i].rect.h);
    }

    code = EntityCodes::metroid;
    for (int i = 0; i < room.metroids.size(); i++) {
        room.metroids[i].texture = IMG_LoadTexture(renderer, ("../assets/" + room.metroids[i].textureFile).c_str());
        SDL_QueryTexture(room.metroids[i].texture, nullptr, nullptr, &room.metroids[i].rect.w, &room.metroids[i].rect.h);
    }
}

void Map::drawFrame(Models::Room &room, Models::Samus &samus) {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, samus.texture, nullptr, &samus.rect);
    for (int i = 0; i < room.blocks.size(); i++) {
        SDL_RenderCopy(renderer, room.blocks[i].texture, nullptr, &room.blocks[i].rect);
    }
    for (int i = 0; i < room.metroids.size(); i++) {
        SDL_RenderCopy(renderer, room.metroids[i].texture, nullptr, &room.metroids[i].rect);
    }
    SDL_RenderPresent(renderer);
}

void Map::destroyTextures(Models::Room &room) {
    for (int i = 0; i < room.blocks.size(); SDL_DestroyTexture(room.blocks[i++].texture));
    for (int i = 0; i < room.metroids.size(); SDL_DestroyTexture(room.metroids[i++].texture));
}

Map::~Map() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
