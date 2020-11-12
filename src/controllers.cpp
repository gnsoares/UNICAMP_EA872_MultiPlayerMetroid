#include <cstdlib>
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "constants.hpp"
#include "controllers.hpp"
#include "utils.hpp"
using namespace Controllers;


/* -=-=-=-=-=-=-=-=-=-=-=-=-  MAP  IMPLEMENTATION  -=-=-=-=-=-=-=-=-=-=-=-=- */
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
    
    // set cooldown to avoid repeated damage
    damageCooldown = 5;

    // decrease hp
    metroid.hp -= SamusConstants::shotDamage;

    // negative hp: set as minimum
    if (metroid.hp < 0) metroid.hp = 0;
    
    // debug damage
    std::cout << "Metroid damage " << metroid.hp << "\n";
}

void Map::update(std::vector<Models::Shot> shots) {
    std::string collision = "";
    int prevX, prevY;

    for (int i = 0; i < room.metroids.size(); i++) {
        prevX = room.metroids[i].rect.x; prevY = room.metroids[i].rect.y;

        // S2 = S1 + V*t + a*t^2/2
        room.metroids[i].rect.x += room.metroids[i].vx + room.metroids[i].ax / 2;
        room.metroids[i].rect.y += room.metroids[i].vy + room.metroids[i].ay / 2;

        // a = -k*x/m
        room.metroids[i].ax = - MetroidConstants::elasticConstantX * (room.metroids[i].rect.x - room.metroids[i].xi) / MetroidConstants::mass;
        room.metroids[i].ay = - MetroidConstants::elasticConstantY * (room.metroids[i].rect.y - room.metroids[i].yi) / MetroidConstants::mass;

        // V2 = V1 + a*t + random factor
        room.metroids[i].vx += room.metroids[i].ax + (rand() % 15 - 7);
        room.metroids[i].vy += room.metroids[i].ay + (rand() % 15 - 7);

        // check collision with blocks
        for (int j = 0; j < room.blocks.size(); j++) {
            if (checkCollision(room.blocks[j].rect, room.metroids[i].rect)) {

                // check which side collided
                collision = collideWithWall(room.metroids[i].rect, room.blocks[i].rect, prevX, prevY);

                // collided with floor
                if (collision == "floor") {

                    // set feet at the top of the block
                    room.metroids[i].rect.y = room.blocks[j].rect.y - room.metroids[i].rect.h;

                    // set acceleration away from floor and set new resting position
                    room.metroids[i].ay -= 5; room.metroids[i].yi -= 5;
                }

                // collided with ceiling: set head at the ceiling
                else if (collision == "ceiling") {

                    // set head at the bottomm of the block
                    room.metroids[i].rect.y = room.blocks[j].rect.y + room.blocks[j].rect.h;

                    // set acceleration away from ceiling and set new resting position
                    room.metroids[i].ay += 5; room.metroids[i].yi -= 5;
                }

                // collided with right wall: set right side at the wall
                else if (collision == "right") {

                    // set right side at the left side of the block
                    room.metroids[i].rect.x = room.blocks[j].rect.x - room.metroids[i].rect.w;

                    // set acceleration away from wall and set new resting position
                    room.metroids[i].ax -= 5; room.metroids[i].xi -= 5;
                }

                // collided with left wall: set left side at the wall
                else if (collision == "left") {

                    // set left side at the right side of the block
                    room.metroids[i].rect.x = room.blocks[j].rect.x + room.blocks[j].rect.w;

                    // set acceleration away from wall and set new resting position
                    room.metroids[i].ax += 5; room.metroids[i].xi -= 5;
                }
            }
        }

        // check collision with doors
        for (int j = 0; j < room.doors.size(); j++) {

            if (checkCollision(room.doors[j].rect, room.metroids[i].rect)) {

                // check which side collided
                collision = collideWithWall(room.metroids[i].rect, room.doors[i].rect, prevX, prevY);

                // collided with floor: set feet at the floor
                if (collision == "floor") {

                    // set feet at the top of the block
                    room.metroids[i].rect.y = room.doors[j].rect.y - room.metroids[i].rect.h;

                    // set acceleration away from floor and set new resting position
                    room.metroids[i].ay -= 5; room.metroids[i].yi -= 5;
                }

                // collided with ceiling: set head at the ceiling
                else if (collision == "ceiling") {

                    // set head at the bottomm of the block
                    room.metroids[i].rect.y = room.doors[j].rect.y + room.doors[j].rect.h;

                    // set acceleration away from ceiling and set new resting position
                    room.metroids[i].ay += 5; room.metroids[i].yi += 5;
                }

                // collided with right wall: set right side at the wall
                else if (collision == "right") {

                    // set right side at the left side of the block
                    room.metroids[i].rect.x = room.doors[j].rect.x - room.metroids[i].rect.w;

                    // set acceleration away from wall and set new resting position
                    room.metroids[i].ax -= 5; room.metroids[i].xi -= 5;
                }

                // collided with left wall: set left side at the wall
                else if (collision == "left") {

                    // set left side at the right side of the block
                    room.metroids[i].rect.x = room.doors[j].rect.x + room.doors[j].rect.w;

                    // set acceleration away from wall and set new resting position
                    room.metroids[i].ax += 5; room.metroids[i].xi += 5;
                }
            }
        }

        // check collision with shots
        if (damageCooldown == 0) {
            for (int j = 0; j < shots.size(); j++) {

                // metroid collided with shot: take damage
                if (checkCollision(shots[j].rect, room.metroids[i].rect)) {
                    damageMetroid(room.metroids[i]);

                    // metroid died: remove it
                    if (room.metroids[i].hp == 0)
                        room.metroids.erase(room.metroids.begin() + i);

                    // no need to check other shots
                    break;
                }
            }
        }
    }

    // decrease cooldown
    if (damageCooldown > 0) damageCooldown--;

    // render map
    mapView.render(room);
}
/* -=-=-=-=-=-=-=-=-=-=-=- END OF MAP IMPLEMENTATION -=-=-=-=-=-=-=-=-=-=-=- */


/* -=-=-=-=-=-=-=-=-=-=-=-=- SAMUS  IMPLEMENTATION -=-=-=-=-=-=-=-=-=-=-=-=- */
Samus::Samus(Models::Samus &samus, Views::Samus &samusView)
    : samus(samus), samusView(samusView) {
    this->samusView.loadTexture(this->samus);
    this->samusView.render(this->samus);
}

void Samus::damage() {
    
    // set cooldown to avoid repeated damage
    damageCooldown = 5;

    // decrease hp
    samus.hp -= MetroidConstants::damage;

    // negative hp: set as minimum
    if (samus.hp < 0) samus.hp = 0;

    // debug damage
    std::cout << "Samus damage " << samus.hp << "\n";
}

void Samus::jump() {

    // Samus already jumping: do nothing
    if (samus.isJumping)
        return;

    // update samus vertical velocity and state
    samus.vy = SamusConstants::jumpVy;

    // set Samus' state
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

    // Samus is in the air: look down
    if (samus.isJumping || samus.isFalling) {
        samus.xSight = 0;
        samus.ySight = 1;
        return;
    }

    // Samus in the ground: morph
    samus.xSight = 0;
    samus.ySight = 0;

    // TODO: check if samus has morphing ball and is not morphed
}

void Samus::moveLeft() {

    // look left
    samus.xSight = -1;
    samus.ySight = 0;

    // walk left
    samus.rect.x -= SamusConstants::horizontalStep;
}

void Samus::moveRight() {

    // look right
    samus.xSight = 1;
    samus.ySight = 0;

    // walk right
    samus.rect.x += SamusConstants::horizontalStep;
}

void Samus::update(std::vector<Models::Block> blocks, std::vector<Models::Door> doors, std::vector<Models::Metroid> metroids) {

    // process user command
    std::string command = samusView.processCommand();
    std::string collision = "";
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

    // not negative velocity: set Samus' state
    if (samus.vy >= 0) samus.isFalling = true;

    // check collision with blocks
    for (int i = 0; i < blocks.size(); i++) {
        if (checkCollision(blocks[i].rect, samus.rect)) {

            // check which side collided
            collision = collideWithWall(samus.rect, blocks[i].rect, prevX, prevY);

            // collided with floor
            if (collision == "floor") {

                // set feet at the top of the block
                samus.rect.y = blocks[i].rect.y - samus.rect.h;

                // update Samus' state
                samus.isJumping = samus.isFalling = false;
            }

            // collided with ceiling
            else if (collision == "ceiling") {

                // set head at the bottomm of the block
                samus.rect.y = blocks[i].rect.y + blocks[i].rect.h;

                // update Samus' state
                samus.isFalling = true;
            }

            // collided with right wall
            else if (collision == "right") {

                // set right side at the left side of the block
                samus.rect.x = blocks[i].rect.x - samus.rect.w;

                // update Samus' state
                samus.isFalling = true;
            }

            // collided with left wall
            else if (collision == "left") {

                // set left side at the right side of the block
                samus.rect.x = blocks[i].rect.x + blocks[i].rect.w;

                // update Samus' state
                samus.isFalling = true;
            }

            // samus must enter free fall if she collides
            if (!samus.isFalling) samus.vy = 0;
        }
    }

    // check collision with doors
    for (int i = 0; i < doors.size(); i++) {

        // door open: ignore
        if (doors[i].isOpen)
            continue;

        // door closed: check collision as same as wall
        if (checkCollision(doors[i].rect, samus.rect)) {

            // check which side collided
            collision = collideWithWall(samus.rect, doors[i].rect, prevX, prevY);

            // collided with floor
            if (collision == "floor") {

                // set feet at the top of the block
                samus.rect.y = doors[i].rect.y - samus.rect.h;

                // update Samus' state
                samus.isJumping = samus.isFalling = false;
            }

            // collided with ceiling
            else if (collision == "ceiling") {

                // set head at the bottomm of the block
                samus.rect.y = doors[i].rect.y + doors[i].rect.h;

                // update Samus' state
                samus.isFalling = true;
            }

            // collided with right wall
            else if (collision == "right") {

                // set right side at the left side of the block
                samus.rect.x = doors[i].rect.x - samus.rect.w;

                // update Samus' state
                samus.isFalling = true;
            }

            // collided with left wall
            else if (collision == "left") {

                // set left side at the right side of the block
                samus.rect.x = doors[i].rect.x + doors[i].rect.w;

                // update Samus' state
                samus.isFalling = true;
            }

            // samus must enter free fall if she collides
            if (!samus.isFalling) samus.vy = 0;
        }
    }

    // check collision with blocks
    if (damageCooldown == 0) {
        for (int i = 0; i < metroids.size(); i++) {

            // Samus collided with a Metroid: take damage
            if (checkCollision(metroids[i].rect, samus.rect)) {
                damage();

                // no need to check more than one metroid
                break;
            }
        }
    }

    // decrease damage cooldown
    if (damageCooldown > 0) damageCooldown--;

    // render Samus
    samusView.render(samus);
}
/* -=-=-=-=-=-=-=-=-=-=-  END OF SAMUS IMPLEMENTATION  -=-=-=-=-=-=-=-=-=-=- */


/* -=-=-=-=-=-=-=-=-=-=-=-=- SHOTS  IMPLEMENTATION -=-=-=-=-=-=-=-=-=-=-=-=- */
Shots::Shots(std::vector<Models::Shot> &shots, Views::Shots &shotsView)
    : shots(shots), shotsView(shotsView) {}

void Shots::createShot(int x, int y, int vx, int vy) {

    // shot cooldown is not zero: block shot creation
    if (shotCooldown != 0) return;

    // create shot, load its texture and add to vector
    Models::Shot shot(x, y, vx, vy);
    shotsView.loadTexture(shot);
    shots.push_back(shot);

    // reset shot cooldown to avoid shot flooding
    shotCooldown = 10;
}

void Shots::update(int x, int y, int vx, int vy) {

    // process user command
    std::string command = shotsView.processCommand();

    // received command to shoot: create shot
    if (command == Commands::shot) createShot(x, y, vx, vy);

    // decrease shot cooldown
    if (shotCooldown > 0) shotCooldown--;

    // update position
    for (int i = 0; i < shots.size(); i++) {
        shots[i].rect.x += shots[i].vx;
        shots[i].rect.y += shots[i].vy;
    }

    // if there is at least one shot and the first exited the window: remove it
    while (shots.size() > 0 && (
           shots[0].rect.x <= 0 ||
           shots[0].rect.y <= 0 ||
           shots[0].rect.x >= Screen::width ||
           shots[0].rect.y >= Screen::height
          ))
        shots.erase(shots.begin());

    // render shots
    shotsView.render(shots);
}
/* -=-=-=-=-=-=-=-=-=-=-  END OF SHOTS IMPLEMENTATION  -=-=-=-=-=-=-=-=-=-=- */
