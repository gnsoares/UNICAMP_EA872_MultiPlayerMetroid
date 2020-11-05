#include <iostream>
#include "../include/metroidController.hpp"
#include "../include/constants.hpp"
#include <memory>
#include <SDL2/SDL.h>

void MetroidPhysics::moleForce(){
    metroid.force = -MetroidMovement::elasticConstant*metroid.rect.x;
}

void MetroidPhysics::acceleration(){
    metroid.acceleration = metroid.force/MetroidCharacteristics::mass;
}

void MetroidPhysics::velocity(){
    metroid.velocity = metroid.velocity+metroid.acceleration*Physics::time;
}

void MetroidPhysics::position(){
    metroid.rect.x = metroid.rect.x + metroid.velocity*Physics::time;
}

void MetroidPhysics::uniformMovement(){
    
}