#include "models.hpp"
using namespace Models;

Entity::Entity(int x, int y) {
    rect.x = x;
    rect.y = y;
}

Shot::Shot(int x, int y, int vx, int vy) : Entity(x, y) {
    this->vx = vx;
    this->vy = vy;
}

Metroid::Metroid(int x, int y) : Entity(x, y) {
    this->xi = x;
    this->yi = y;
}
