#include <string>
#include <SDL2/SDL_image.h>
#include "constants.hpp"

class Entity {
    public:
        explicit Entity(int x, int y);
        SDL_Texture *texture = nullptr;
        SDL_Rect rect;
};

class Samus:public Entity {
    using Entity::Entity;
    public:
        int hp;
        int missileCounter;
        float verticalVelocity = SamusMovement::initialVerticalVelocity;
        std::string state;
};

class Metroid:public Entity {
    using Entity::Entity;
    public:
        int hp;
        float force;
        float acceleration;
        float velocity;
};

class MotherBrain:public Entity {
    using Entity::Entity;
    public:
        int hp;
};

class Block:public Entity {
    using Entity::Entity;
    public:
        std::string type;
};

class MorphingBall:public Entity {
    using Entity::Entity;
};

class Shot:public Entity {
    using Entity::Entity;
};

class MissileShot:public Entity {
    using Entity::Entity;
};

class MissileDrop:public Entity {
    using Entity::Entity;
};

class HPDrop:public Entity {
    using Entity::Entity;
};
