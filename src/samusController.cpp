#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include "../include/constants.hpp"
#include "../include/samusController.hpp"

void SamusPhysics::jumpingAceleration(){
    float samusV;
    samusV = samus.verticalVelocity - Physics::gravity*Physics::time;
    samus.verticalVelocity = samusV;
}


void SamusPhysics::jumpingPosition(){
    samus.rect.x = samus.rect.x + samus.verticalVelocity*Physics::time - (Physics::gravity*Physics::time^2)/2;
}

void SamusPhysics::walking(){
    float posicao = 0;
    if (state[SDL_SCANCODE_LEFT])
    posicao = samus.rect.x + 0.1;
    if (state[SDL_SCANCODE_RIGHT])
    posicao = samus.rect.x - 0.1;

    samus.rect.x = posicao;
}

void SamusPhysics::update(){
    SDL_PumpEvents();
    if(state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_RIGHT])
        walking();
    if (state[SDL_SCANCODE_UP]){
        jumpingAceleration();
        jumpingPosition();
    }
}