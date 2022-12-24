#include "models.hpp"
using namespace Models;

Entity::Entity() {}
Entity::Entity(int x, int y) {
    rect.x = x;
    rect.y = y;
}

Shot::Shot(int x, int y, int vx, int vy) : Entity(x, y) {
    this->vx = vx;
    this->vy = vy;
}
Shot::Shot(json shot) : Entity() {
    if (shot.contains("rect.x") && shot["rect.x"] != nullptr)
        rect.x = shot["rect.x"];
    if (shot.contains("rect.y") && shot["rect.y"] != nullptr)
        rect.y = shot["rect.y"];
    if (shot.contains("vx") && shot["vx"] != nullptr)
        vx = shot["vx"];
    if (shot.contains("vy") && shot["vy"] != nullptr)
        vy = shot["vy"];
}

Samus::Samus() : Entity() {}
Samus::Samus(int x, int y) : Entity(x, y) {}
Samus::Samus(json samus) : Entity()  {
    if (samus.contains("rect.x") && samus["rect.x"] != nullptr)
        rect.x = samus["rect.x"];
    if (samus.contains("rect.y") && samus["rect.y"] != nullptr)
        rect.y = samus["rect.y"];
    // missileCounter = samus["missileCounter"];
    // vy = samus["vy"];
    // xSight = samus["xSight"];
    // ySight = samus["ySight"];
    // isJumping = samus["isJumping"];
    // isFalling = samus["isFalling"];
    if (samus.contains("hp") && samus["hp"] != nullptr)
        hp = samus["hp"];
    // state = samus["state"];
}

void Samus::update(json samus) {
    if (samus.contains("rect.x") && samus["rect.x"] != nullptr)
        rect.x = samus["rect.x"];
    if (samus.contains("rect.y") && samus["rect.y"] != nullptr)
        rect.y = samus["rect.y"];
    // missileCounter = samus["missileCounter"];
    // vy = samus["vy"];
    // xSight = samus["xSight"];
    // ySight = samus["ySight"];
    // isJumping = samus["isJumping"];
    // isFalling = samus["isFalling"];
    if (samus.contains("hp") && samus["hp"] != nullptr)
        hp = samus["hp"];
    // state = samus["state"];
}

Metroid::Metroid() : Entity() {}
Metroid::Metroid(int x, int y) : Entity(x, y) {
    this->xi = x;
    this->yi = y;
}
