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

void Samus::jump() {

    // Samus already jumping: do nothing
    if (samus.state == SamusMovement::jumpingState)
        return;

    // Samus is morphed: unmorph
    if (samus.state == SamusMovement::morphedState) {
        samus.state = SamusMovement::idleState;
        return;
    }

    // update samus vertical velocity and state
    samus.verticalVelocity = SamusMovement::initialVerticalVelocity;
    samus.state = SamusMovement::jumpingState;
}

void Samus::lookUp() {

    // Samus already jumping: do nothing
    if (samus.state == SamusMovement::idleState)
        return;

    // update samus state
    samus.state = SamusMovement::aimingUpState;
}

void Samus::morph() {
    // TODO: check if samus has morphing ball and is not morphed
}

void Samus::moveLeft() {
    samus.rect.x -= SamusMovement::horizontalStep;
}

void Samus::moveRight() {
    samus.rect.x += SamusMovement::horizontalStep;
}

void Samus::update() {
    std::string command = samusView.processCommand();

    if (command == Commands::jump) jump();
    if (command == Commands::lookUp) lookUp();
    if (command == Commands::morph) morph();
    if (command == Commands::moveLeft) moveLeft();
    if (command == Commands::moveRight) moveRight();

    // TODO: update Samus vertical position based on vertical velocity
}

void Samus::jumpingAceleration() {
    float samusV;
    samusV = samus.verticalVelocity - Physics::gravity * Physics::time;
    samus.verticalVelocity = samusV;
}

void Samus::jumpingPosition() {
    samus.rect.x += samus.verticalVelocity * Physics::time -
                   ( Physics::gravity * Physics::time^2 ) / 2;
}
