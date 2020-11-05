#ifndef METROID_MODELS_H
#define METROID_MODELS_H

#include <string>
#include <vector>
#include <SDL2/SDL.h>


namespace Models {
    class Entity {
        public:

            /*! \brief Entity constructor
            *
            * \param x entity x coordinate
            * \param y entity y coordinate
            * \param w entity width
            * \param h entity height
            */
            explicit Entity(int x, int y, int w, int h);
            SDL_Texture *texture = nullptr;
            std::string textureFile;
            SDL_Rect rect;
    };

    class Samus:public Entity {
        using Entity::Entity;
        public:
            int hp;
            int missileCounter;
            float mass;
            float verticalVelocity;
            std::string state;
    };

    class Metroid:public Entity {
        using Entity::Entity;
        public:
            int hp;
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

    class Door:public Entity {
        using Entity::Entity;
        public:
            std::string leadsTo;
    };

    class Room {
        public:
            std::vector<Block> blocks;
            std::vector<Door> doors;
            std::vector<Metroid> metroids;
            MorphingBall *morphingball = nullptr;
            MotherBrain *motherbrain = nullptr;
    };
}

#endif
