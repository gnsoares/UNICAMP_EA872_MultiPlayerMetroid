#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/views.hpp"

void View::setXS(int x) {target.x = x;}

int View::getXS() {return target.x;}

void View::setYS(int y) {target.y = y;}

int View::getYS() {return target.y;}

const int View::getAltura() {return altura;}
const int View::getLargura() {return largura;}

View::View() {
    window = SDL_CreateWindow(
        " SDL2",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        largura,
        altura,
        SDL_WINDOW_SHOWN
    );
    if (window == nullptr) { // Em caso de erro...
        std::cout << SDL_GetError();
        SDL_Quit();
   	}
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) { // Em caso de erro...
        SDL_DestroyWindow(window);
        std::cout << SDL_GetError();
        SDL_Quit();
    }
    texture = IMG_LoadTexture(renderer, "../assets/samus.png");
    target.x = 0;
    target.y = 0;
    SDL_QueryTexture(texture, nullptr, nullptr, &target.w, &target.h);
}

View::~View() {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Rect View::getTarget() {
    return target;
}

void View::draw() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, &target);
    SDL_RenderPresent(renderer);
}