#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include "constants.hpp"
#include "controllers.hpp"


Controllers::Map::Map(Models::Room &room, Models::Samus &samus) : room(room), samus(samus) {
    this->room = room;
    this->samus = samus;
}

void Controllers::Map::changeRooms(Models::Room &room) {
    mapView.destroyTextures(this->room);
    mapView.initializeRoom(room, samus);
    mapView.drawFrame(room, samus);
    this->room = room;
}

void Controllers::Map::update() {
    mapView.drawFrame(room, samus);
}

void Controllers::Metroid::moleForce() {
    // metroid.force = -MetroidMovement::elasticConstant * metroid.rect.x;
}

void Controllers::Metroid::acceleration() {
    // metroid.acceleration = metroid.force / MetroidCharacteristics::mass;
}

void Controllers::Metroid::velocity() {
    // metroid.velocity = metroid.velocity + metroid.acceleration * Physics::time;
}

void Controllers::Metroid::position() {
    // metroid.rect.x = metroid.rect.x + metroid.velocity * Physics::time;
}

void Controllers::Metroid::uniformMovement() {
    // implement later
}

Controllers::Samus::Samus(Models::Samus &samus) : samus(samus) {
    state = SDL_GetKeyboardState(nullptr);
}


void Controllers::Samus::jumpingAceleration() {
    float samusV;
    samusV = samus.verticalVelocity - Physics::gravity * Physics::time;
    samus.verticalVelocity = samusV;
}


void Controllers::Samus::jumpingPosition() {
    samus.rect.x += samus.verticalVelocity * Physics::time -
                   ( Physics::gravity * Physics::time^2 ) / 2;
}

void Controllers::Samus::walking() {
    if (state[SDL_SCANCODE_LEFT])
        samus.rect.x += 0.1;
    if (state[SDL_SCANCODE_RIGHT])
        samus.rect.x -= 0.1;
}

void Controllers::Samus::update() {
    SDL_PumpEvents();
    if(state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_RIGHT])
        walking();
    if (state[SDL_SCANCODE_UP]) {
        jumpingAceleration();
        jumpingPosition();
    }
}