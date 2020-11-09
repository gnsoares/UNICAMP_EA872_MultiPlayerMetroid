#include "models.hpp"
using namespace Models;

Entity::Entity(int x, int y, int w, int h) {
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}

void ShotVector::addShot(int rectx, int recty, int rectw, int recth){
    bullets.push_back(Shot(rectx, recty, rectw, recth));
}

void ShotVector::updateShot(int rectx, int i){
    bullets.at(i).rect.x = rectx;
}

void ShotVector::eraseShot(int i){
    //delete bullets.at(i);
    bullets.erase(bullets.begin()+i);
}

Shot ShotVector::returnShotX(int i){
    return bullets.at(i);
}

int ShotVector::returnLenghtShot(){
    return bullets.size();
}

void Room::updateMetroidLife(int hp, int i){
    metroids.at(i).hp = hp;
}

void Room::updateMetroidPosition(int rectx, int i){
    metroids.at(i).rect.x = rectx;
}

void Room::eraseMetroid(int i){
    metroids.erase(metroids.begin()+i);
}

Metroid Room::returnMetroid(int i){
    return metroids.at(i);
}

int Room::returnLenghtMetroid(){
    return metroids.size();
}
