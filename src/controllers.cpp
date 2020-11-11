#include <SDL2/SDL.h>
#include <vector>
#include "constants.hpp"
#include "controllers.hpp"
using namespace Controllers;


Map::Map(Models::Room &room, Views::Map &mapView)
    : room(room), mapView(mapView) {
    this->mapView.initializeRoom(this->room);
    this->mapView.render(this->room);
}

void Map::changeRooms(Models::Room &room) {
    mapView.destroyTextures(this->room);
    mapView.initializeRoom(room);
    mapView.render(room);
    this->room = room;
}

void Map::update() {
    mapView.render(room);
}

Samus::Samus(Models::Samus &samus, Views::Samus &samusView)
    : samus(samus), samusView(samusView) {
    this->samusView.loadTexture(this->samus);
    this->samusView.render(this->samus);
}

void Samus::jump() {

    // Samus already jumping: do nothing
    if (samus.state == SamusConstants::jumpingState)
        return;

    // update samus vertical velocity and state
    samus.vy = SamusConstants::jumpVy;
    samus.state = SamusConstants::jumpingState;
}

void Samus::lookUp() {

    // Samus is morphed: unmorph
    if (samus.state == SamusConstants::morphedState) {
        samus.state = SamusConstants::idleState;
        return;
    }

    // update samus sight
    samus.ySight = -1;
    samus.xSight = 0;
}

void Samus::morph() {
    samus.xSight = 0;
    samus.ySight = 0;
    // TODO: check if samus has morphing ball and is not morphed
}

void Samus::moveLeft() {
    samus.xSight = -1;
    samus.ySight = 0;
    samus.rect.x -= SamusConstants::horizontalStep;
}

void Samus::moveRight() {
    samus.xSight = 1;
    samus.ySight = 0;
    samus.rect.x += SamusConstants::horizontalStep;
}

void Samus::update() {
    std::string command = samusView.processCommand();

    if (command == Commands::jump) jump();
    if (command == Commands::lookUp) lookUp();
    if (command == Commands::morph) morph();
    if (command == Commands::moveLeft) moveLeft();
    if (command == Commands::moveRight) moveRight();

    // TODO: update Samus vertical position based on vertical velocity

    samusView.render(samus);
}

void Samus::jumpingAceleration() {
    samus.vy -= Physics::gravity * Physics::time;
}

void Samus::jumpingPosition() {
    samus.rect.y -= samus.vy * Physics::time -
                   ( Physics::gravity * Physics::time * Physics::time ) / 2;
}

Shots::Shots(std::vector<Models::Shot> &shots, Views::Shots &shotsView)
    : shots(shots), shotsView(shotsView) {}

void Shots::createShot(int x, int y, int vx, int vy) {
    Models::Shot shot(x, y, vx, vy);
    shotsView.loadTexture(shot);
    shots.push_back(shot);
}

void Shots::update(int x, int y, int vx, int vy) {

    std::string command = shotsView.processCommand();

    if (command == Commands::shot) createShot(x, y, vx, vy);

    for (int i = 0; i < shots.size(); i++) {
        shots[i].rect.x += shots[i].vx;
        shots[i].rect.y += shots[i].vy;
    }

    while (shots.size() > 0 && (
           shots[0].rect.x <= 0 ||
           shots[0].rect.y <= 0 ||
           shots[0].rect.x >= Screen::width ||
           shots[0].rect.y >= Screen::height
          ))
        shots.erase(shots.begin());

    shotsView.render(shots);
}
