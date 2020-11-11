#ifndef METROID_MODELS_H
#define METROID_MODELS_H

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "constants.hpp"


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
            int hp = SamusConstants::initialHP; /*!< Samus' hp */
            int missileCounter = 0;
            int vy = 0; /*!< Samus' velocity */
            int xSight = 1; /*!< where Samus is looking */
            int ySight = 0; /*!< where Samus is looking */
            bool isJumping = false;
            bool isFalling = false;
            std::string state; /*!< Samus' state */

    };

    class Metroid:public Entity {
        using Entity::Entity;
        public:
            explicit Metroid(int x, int y);
            int hp = MetroidConstants::initialHP; /*!< Metroid's hp */
            int xi;
            int yi;
            int ax = 0; /*!< Metroid's initial acceleration */
            int ay = 0; /*!< Metroid's initial acceleration */
            int vx = MetroidConstants::maxVx; /*!< Metroid's initial velocity*/
            int vy = MetroidConstants::maxVy; /*!< Metroid's initial velocity*/
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
