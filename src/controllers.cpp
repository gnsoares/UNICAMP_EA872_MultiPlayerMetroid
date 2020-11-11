#include <cstdlib>
#include <vector>
#include <SDL2/SDL.h>
#include "constants.hpp"
#include "controllers.hpp"
#include "utils.hpp"
using namespace Controllers;

#include <iostream>
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

void Map::damageMetroid(Models::Metroid &metroid) {
    damageCooldown = 5;
    metroid.hp -= SamusConstants::shotDamage;
    if (metroid.hp < 0) metroid.hp = 0;
    std::cout << "Metroid damage " << metroid.hp << "\n";
}

void Map::update(std::vector<Models::Shot> shots) {

    for (int i = 0; i < room.metroids.size(); i++) {
        int prevX = room.metroids[i].rect.x, prevY = room.metroids[i].rect.y;

        room.metroids[i].rect.x += room.metroids[i].vx + room.metroids[i].ax / 2;
        room.metroids[i].rect.y += room.metroids[i].vy + room.metroids[i].ay / 2;

        room.metroids[i].ax = - MetroidConstants::elasticConstantX * (room.metroids[i].rect.x - room.metroids[i].xi) / MetroidConstants::mass;
        room.metroids[i].ay = - MetroidConstants::elasticConstantY * (room.metroids[i].rect.y - room.metroids[i].yi) / MetroidConstants::mass;

        room.metroids[i].vx += room.metroids[i].ax + (rand() % 15 - 7);
        room.metroids[i].vy += room.metroids[i].ay + (rand() % 15 - 7);

        // std::cout << "(x = " << room.metroids[i].rect.x << ", y = " << room.metroids[i].rect.y << ") \n";
        // std::cout << "(vx = " << room.metroids[i].vx << ", vy = " << room.metroids[i].vy << ") \n";
        // std::cout << "(ax = " << room.metroids[i].ax << ", ay = " << room.metroids[i].ay << ") \n\n";

        // check collision with blocks
        for (int j = 0; j < room.blocks.size(); j++) {

            if (checkCollision(room.blocks[j].rect, room.metroids[i].rect)) {

                // collided with floor: set feet at the floor
                if (room.metroids[i].rect.y + room.metroids[i].rect.h >= room.blocks[j].rect.y &&
                    prevY + room.metroids[i].rect.h <= room.blocks[j].rect.y) {
                    room.metroids[i].rect.y = room.blocks[j].rect.y - room.metroids[i].rect.h;
                    room.metroids[i].ay -= 5;
                    room.metroids[i].yi -= 5;
                }

                // collided with ceiling: set head at the ceiling
                else if (room.blocks[j].rect.y + room.blocks[j].rect.h >= room.metroids[i].rect.y &&
                         room.blocks[j].rect.y + room.blocks[j].rect.h <= prevY) {
                    room.metroids[i].rect.y = room.blocks[j].rect.y + room.blocks[j].rect.h;
                    room.metroids[i].ay += 5;
                    room.metroids[i].yi -= 5;
                }

                // collided with right wall: set right side at the wall
                else if (room.metroids[i].rect.x + room.metroids[i].rect.w >= room.blocks[j].rect.x &&
                         prevX + room.metroids[i].rect.w <= room.blocks[j].rect.x) {
                    room.metroids[i].rect.x = room.blocks[j].rect.x - room.metroids[i].rect.w;
                    room.metroids[i].ax -= 5;
                    room.metroids[i].xi -= 5;
                }

                // collided with left wall: set left side at the wall
                else if (room.blocks[j].rect.x + room.blocks[j].rect.w >= room.metroids[i].rect.x &&
                         room.blocks[j].rect.x + room.blocks[j].rect.w <= prevX) {
                    room.metroids[i].rect.x = room.blocks[j].rect.x + room.blocks[j].rect.w;
                    room.metroids[i].ax += 5;
                    room.metroids[i].xi -= 5;
                }
            }
        }

        // check collision with doors
        for (int j = 0; j < room.doors.size(); j++) {

            if (checkCollision(room.doors[j].rect, room.metroids[i].rect)) {

                // collided with floor: set feet at the floor
                if (room.metroids[i].rect.y + room.metroids[i].rect.h >= room.doors[j].rect.y &&
                    prevY + room.metroids[i].rect.h <= room.doors[j].rect.y) {
                    room.metroids[i].rect.y = room.doors[j].rect.y - room.metroids[i].rect.h;
                    room.metroids[i].ay -= 5;
                    room.metroids[i].yi -= 5;
                }

                // collided with ceiling: set head at the ceiling
                else if (room.doors[j].rect.y + room.doors[j].rect.h >= room.metroids[i].rect.y &&
                         room.doors[j].rect.y + room.doors[j].rect.h <= prevY) {
                    room.metroids[i].rect.y = room.doors[j].rect.y + room.doors[j].rect.h;
                    room.metroids[i].ay += 5;
                    room.metroids[i].yi += 5;
                }

                // collided with right wall: set right side at the wall
                else if (room.metroids[i].rect.x + room.metroids[i].rect.w >= room.doors[j].rect.x &&
                         prevX + room.metroids[i].rect.w <= room.doors[j].rect.x) {
                    room.metroids[i].rect.x = room.doors[j].rect.x - room.metroids[i].rect.w;
                    room.metroids[i].ax -= 5;
                    room.metroids[i].xi -= 5;
                }

                // collided with left wall: set left side at the wall
                else if (room.doors[j].rect.x + room.doors[j].rect.w >= room.metroids[i].rect.x &&
                         room.doors[j].rect.x + room.doors[j].rect.w <= prevX) {
                    room.metroids[i].rect.x = room.doors[j].rect.x + room.doors[j].rect.w;
                    room.metroids[i].ax += 5;
                    room.metroids[i].xi += 5;
                }
            }
        }

        // check collision with shots
        if (damageCooldown == 0) {
            for (int j = 0; j < shots.size(); j++) {
                if (checkCollision(shots[j].rect, room.metroids[i].rect)) {
                    damageMetroid(room.metroids[i]);
                    break;
                }
            }
        }
    }

    if (damageCooldown > 0) damageCooldown--;

    mapView.render(room);
}

Samus::Samus(Models::Samus &samus, Views::Samus &samusView)
    : samus(samus), samusView(samusView) {
    this->samusView.loadTexture(this->samus);
    this->samusView.render(this->samus);
}

void Samus::damage() {
    damageCooldown = 5;
    samus.hp -= MetroidConstants::damage;
    if (samus.hp < 0) samus.hp = 0;
    std::cout << "Samus damage " << samus.hp << "\n";
}

void Samus::jump() {

    // Samus already jumping: do nothing
    if (samus.isJumping)
        return;

    // update samus vertical velocity and state
    samus.vy = SamusConstants::jumpVy;
    samus.isJumping = true;
    samus.isFalling = false;
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

    if (samus.isJumping || samus.isFalling) {
        samus.xSight = 0;
        samus.ySight = 1;
        return;
    }

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

void Samus::update(std::vector<Models::Block> blocks, std::vector<Models::Door> doors, std::vector<Models::Metroid> metroids) {

    // process user command
    std::string command = samusView.processCommand();
    int prevX = samus.rect.x, prevY = samus.rect.y;

    // execute user command
    if (command == Commands::jump) jump();
    if (command == Commands::lookUp) lookUp();
    if (command == Commands::morph) morph();
    if (command == Commands::moveLeft) moveLeft();
    if (command == Commands::moveRight) moveRight();

     // set new vertical position
    samus.rect.y += samus.vy + SamusConstants::gravity / 2;

    // set new vertical velocity
    samus.vy += SamusConstants::gravity;

    // check collision with blocks
    for (int i = 0; i < blocks.size(); i++) {
        if (checkCollision(blocks[i].rect, samus.rect)) {

            // collided with floor: set feet at the floor
            if (samus.rect.y + samus.rect.h >= blocks[i].rect.y &&
                prevY + samus.rect.h <= blocks[i].rect.y) {
                samus.rect.y = blocks[i].rect.y - samus.rect.h;
                samus.isJumping = samus.isFalling = false;
            }

            // collided with ceiling: set head at the ceiling
            else if (blocks[i].rect.y + blocks[i].rect.h >= samus.rect.y &&
                blocks[i].rect.y + blocks[i].rect.h <= prevY) {
                samus.rect.y = blocks[i].rect.y + blocks[i].rect.h;
                samus.isFalling = true;
            }

            // collided with right wall: set right side at the wall
            else if (samus.rect.x + samus.rect.w >= blocks[i].rect.x &&
                prevX + samus.rect.w <= blocks[i].rect.x) {
                samus.rect.x = blocks[i].rect.x - samus.rect.w;
                samus.isFalling = true;
            }

            // collided with left wall: set left side at the wall
            else if (blocks[i].rect.x + blocks[i].rect.w >= samus.rect.x &&
                blocks[i].rect.x + blocks[i].rect.w <= prevX) {
                samus.rect.x = blocks[i].rect.x + blocks[i].rect.w;
                samus.isFalling = true;
            }

            // samus must enter free fall if she collides
            if (!samus.isFalling) samus.vy = 0;
        }
    }

    // check collision with doors
    for (int i = 0; i < doors.size(); i++) {
        if (checkCollision(doors[i].rect, samus.rect)) {

            // collided with floor: set feet at the floor
            if (samus.rect.y + samus.rect.h >= doors[i].rect.y &&
                prevY + samus.rect.h <= doors[i].rect.y) {
                samus.rect.y = doors[i].rect.y - samus.rect.h;
                samus.isJumping = samus.isFalling = false;
            }

            // collided with ceiling: set head at the ceiling
            else if (doors[i].rect.y + doors[i].rect.h >= samus.rect.y &&
                doors[i].rect.y + doors[i].rect.h <= prevY) {
                samus.rect.y = doors[i].rect.y + doors[i].rect.h;
                samus.isFalling = true;
            }

            // collided with right wall: set right side at the wall
            else if (samus.rect.x + samus.rect.w >= doors[i].rect.x &&
                prevX + samus.rect.w <= doors[i].rect.x) {
                samus.rect.x = doors[i].rect.x - samus.rect.w;
                samus.isFalling = true;
            }

            // collided with left wall: set left side at the wall
            else if (doors[i].rect.x + doors[i].rect.w >= samus.rect.x &&
                doors[i].rect.x + doors[i].rect.w <= prevX) {
                samus.rect.x = doors[i].rect.x + doors[i].rect.w;
                samus.isFalling = true;
            }

            // samus must enter free fall if she collides
            if (!samus.isFalling) samus.vy = 0;
        }
    }

    // check collision with blocks
    if (damageCooldown == 0) {
        for (int i = 0; i < metroids.size(); i++) {
            if (checkCollision(metroids[i].rect, samus.rect)) {
                damage();
                break;
            }
        }
    }

    if (damageCooldown > 0) damageCooldown--;

    samusView.render(samus);
}

Shots::Shots(std::vector<Models::Shot> &shots, Views::Shots &shotsView)
    : shots(shots), shotsView(shotsView) {}

void Shots::createShot(int x, int y, int vx, int vy) {
    if (shotCooldown != 0) return;
    Models::Shot shot(x, y, vx, vy);
    shotsView.loadTexture(shot);
    shots.push_back(shot);
    shotCooldown = 10;
}

void Shots::update(int x, int y, int vx, int vy) {

    std::string command = shotsView.processCommand();

    if (command == Commands::shot) createShot(x, y, vx, vy);

    if (shotCooldown > 0) shotCooldown--;

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
