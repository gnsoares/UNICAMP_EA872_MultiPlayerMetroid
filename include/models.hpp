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
            */
            explicit Entity(int x, int y);
            SDL_Texture *texture = nullptr;
            SDL_Rect rect;
    };

    class Samus:public Entity {
        using Entity::Entity;
        public:
            int hp = 100; /*!< Samus' hp */
            int missileCounter;
            int mass;
            int vy; /*!< Samus' velocity */
            int xSight = 1; /*!< where Samus is looking */
            int ySight = 0; /*!< where Samus is looking */
            std::string state; /*!< Samus' state */

    };

    class Metroid:public Entity {
        using Entity::Entity;
        public:
            int hp = 50; /*!< Metroid's hp */
            int force = 0; /*!< Metroid's force (movement)*/
            int acceleration = 0; /*!< Metroid's initial acceleration */
            int velocity = 1; /*!< Metroid's initial velocity*/
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
        public:
            explicit Shot(int x, int y, int vx, int vy);
            int vx;
            int vy;
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
            std::vector<Block> blocks; /*!< Vector of Block objects*/
            std::vector<Door> doors; /*!< Vector of Door objects*/
            std::vector<Metroid> metroids; /*!< Vector of Metroid objects*/
            MorphingBall *morphingball = nullptr;
            MotherBrain *motherbrain = nullptr;
    };
}

#endif
