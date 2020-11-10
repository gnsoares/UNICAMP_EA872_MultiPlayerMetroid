#include <SDL2/SDL.h>
#include "constants.hpp"
#include "controllers.hpp"
#include <iostream>
using namespace Controllers;


Map::Map(Models::Room &room, Models::Samus &samus, Models::ShotVector &bullets) : room(room), samus(samus), bullets(bullets) {}

void Map::changeRooms(Models::Room &room) {
    mapView.destroyTextures(this->room);
    mapView.initializeRoom(room, samus, bullets);
    mapView.drawFrame(room, samus, bullets);
    this->room = room;
}

void Map::update() {
    mapView.drawFrame(room, samus, bullets);
}

/*
void Map::shotsCollisions(){
    int shotsNumber = room.returnLenghtShot();
    int metroidNumber = room.returnLenghtMetroid();

    for (int i=0; i<shotsNumber; i++){
        for(int j=0; j<metroidNumber; j++){
            Models::Shot shotPosition = room.returnShotX(i);
            Models::Metroid metroidPosition = room.returnMetroid(i);
            //Checks collision between Metroid and Shot
            bool shotCollided = checkCollision(metroidPosition.rect, shotPosition.rect);
            //If they're collinding, metroid takes a hit
            if (shotCollided){
                room.eraseShot(i);
                metroidPosition.hp -= 10;
                room.updateMetroidLife(metroidPosition.hp, j);
            }
            //Metroid's death
            if (metroidPosition.hp == 0){
                room.eraseMetroid(j);
            }

            //Samus loses life
            bool samusCollided = checkCollision(metroidPosition.rect, samus.rect);
            
            if (samusCollided){
                samus.hp -= 10;
            }
        }
    }
}
*/

void Map::metroidPosition(){
    int metroidNumber = room.returnLenghtMetroid();
    for(int i = 0; i<metroidNumber; i++){
        Models::Metroid metroidMole = room.returnMetroid(i);
        metroidMole.force = -MetroidMovement::elasticConstant * metroidMole.rect.x;
        metroidMole.acceleration = metroidMole.force/MetroidMovement::mass;
        metroidMole.velocity = metroidMole.velocity + metroidMole.acceleration*Physics::time;
        metroidMole.rect.x = metroidMole.rect.x + metroidMole.velocity * Physics::time;
    }
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

Shots::Shots(Models::Shot &shots, Models::ShotVector &bullet, Models::Samus &samus): shots(shots), bullet(bullet), samus(samus){}

void Shots::saveShotPosition(){
        int initialPositionY = samus.rect.y + samus.rect.h/2;
        int initialPositionX = samus.rect.x + samus.rect.w/2;
        bullet.addShot(initialPositionX, initialPositionY, 1, 2);
}

void Shots::updateShotPosition(){
    int shotsNumber = bullet.returnLenghtShot();
    for (int i=0; i<shotsNumber; i++){
        Models::Shot updatedShot = bullet.returnShotX(i);
        int updatedX = 1 + updatedShot.rect.x;
        bullet.updateShot(updatedX, i);
    }
}

void Shots::update(){
    std::string command = shotsView.processCommand();

    if (command == Commands::shot){
        saveShotPosition();
    }
    updateShotPosition();
}