#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "view.hpp"

void View::setX(int x) {target.x = x;}

int View::getX() {return target.x;}

void View::setY(int y) {target.y = y;}

int View::getY() {return target.y;}

const int View::getAltura() {return altura;}
const int View::getLargura() {return largura;}

void View::imprimirCoordenadas() {std::cout << '(' << target.x << ',' << target.y << ')' << std::endl;}

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
    texture = IMG_LoadTexture(renderer, "./metal-texture-24-mini.jpg");
    target.x = largura/2;
    target.y = altura/2;
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