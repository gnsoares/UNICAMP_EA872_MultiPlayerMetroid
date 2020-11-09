#include <iostream>
#include <memory>
#include <SDL2/SDL.h>
#include "constants.hpp"
#include "controllers.hpp"
using namespace Controllers;


Map::Map(Models::Room &room, Models::Samus &samus) : room(room), samus(samus) {}

void Map::changeRooms(Models::Room &room) {
    mapView.destroyTextures(this->room);
    mapView.initializeRoom(room, samus);
    mapView.drawFrame(room, samus);
    this->room = room;
}

void Map::update() {
    mapView.drawFrame(room, samus);
}

void Metroid::moleForce() {
    // metroid.force = -MetroidMovement::elasticConstant * metroid.rect.x;
}

void Metroid::acceleration() {
    // metroid.acceleration = metroid.force / MetroidCharacteristics::mass;
}

void Metroid::velocity() {
    // metroid.velocity = metroid.velocity + metroid.acceleration * Physics::time;
}

void Metroid::position() {
    // metroid.rect.x = metroid.rect.x + metroid.velocity * Physics::time;
}

void Metroid::uniformMovement() {
    // implement later
}

Samus::Samus(Models::Samus &samus) : samus(samus) {}


void Samus::jumpingAceleration() {
    float samusV;
    samusV = samus.verticalVelocity - Physics::gravity * Physics::time;
    samus.verticalVelocity = samusV;
}


void Samus::jumpingPosition() {
    samus.rect.x += samus.verticalVelocity * Physics::time -
                   ( Physics::gravity * Physics::time^2 ) / 2;
}

void Samus::walking() {
    if (state[SDL_SCANCODE_LEFT])
        samus.rect.x += 0.1;
    if (state[SDL_SCANCODE_RIGHT])
        samus.rect.x -= 0.1;
}

void Samus::update() {
    SDL_PumpEvents();
    if(state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_RIGHT])
        walking();
    if (state[SDL_SCANCODE_UP]) {
        jumpingAceleration();
        jumpingPosition();
    }
}
