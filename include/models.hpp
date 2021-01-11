#ifndef METROID_MODELS_H
#define METROID_MODELS_H

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include "constants.hpp"
#include "json.hpp"

using nlohmann::json;

namespace Models {
    class Entity {
        public:
            SDL_Texture *texture = nullptr;
            SDL_Rect rect;

            /*! \brief Entity constructor
             *
             * \param x entity x coordinate
             * \param y entity y coordinate
             */
            explicit Entity(int x, int y);
            explicit Entity();
    };

    class Samus:public Entity {
        using Entity::Entity;
        public:
            int hp = SamusConstants::initialHP; /*!< Samus' hp */
            int missileCounter = 0;
            int vy = 0; /*!< Samus' vertical velocity */
            int xSight = 1; /*!< where Samus is looking horizontally */
            int ySight = 0; /*!< where Samus is looking vertically */
            bool isJumping = false; /*!< whether or not Samus is jumping */
            bool isFalling = false; /*!< whether or not Samus is falling */
            std::string state; /*!< Samus' state */

            explicit Samus();
            explicit Samus(json samus);
            explicit Samus(int x, int y);

            void update(json samus);

            NLOHMANN_DEFINE_TYPE_INTRUSIVE(Samus,
                                           rect.x,
                                           rect.y,
                                           missileCounter,
                                           vy,
                                           xSight,
                                           ySight,
                                           isJumping,
                                           isFalling,
                                           hp,
                                           state);
    };

    class Metroid:public Entity {
        using Entity::Entity;
        public:
            int hp = MetroidConstants::initialHP; /*!< Metroid's hp */
            int xi; /*!< Metroid's resting horizontal position */
            int yi; /*!< Metroid's resting vertical position */
            int ax = 0; /*!< Metroid's initial acceleration horizontally */
            int ay = 0; /*!< Metroid's initial acceleration vertically */
            int vx = MetroidConstants::maxVx; /*!< Metroid's initial velocity horizontally */
            int vy = MetroidConstants::maxVy; /*!< Metroid's initial velocity vertically */

            /*! \brief Metroid constructor
             *
             * \param x entity x coordinate
             * \param y entity y coordinate
             */
            explicit Metroid(int x, int y);
            explicit Metroid();

            NLOHMANN_DEFINE_TYPE_INTRUSIVE(Metroid,
                                           hp,
                                           rect.x,
                                           rect.y,
                                           xi,
                                           yi,
                                           ax,
                                           ay,
                                           vx,
                                           vy);
    };

    class MotherBrain:public Entity {
        using Entity::Entity;
        public:
            int hp; /*!< MotherBrain's hp */
    };

    class Block:public Entity {
        using Entity::Entity;
        public:
            std::string type; /*!< Block type */

            NLOHMANN_DEFINE_TYPE_INTRUSIVE(Block,
                                           rect.x,
                                           rect.y,
                                           type);
    };

    class MorphingBall:public Entity {
        using Entity::Entity;
    };

    class Shot:public Entity {
        using Entity::Entity;
        public:
            int vx; /*!< Shot's velocity horizontally */
            int vy; /*!< Shot's velocity vertically */

            /*! \brief Shot constructor
             *
             * \param x shot x coordinate
             * \param y shot y coordinate
             * \param vx shot horizontal velocity
             * \param vy shot vertical velocity
             */
            explicit Shot(int x, int y, int vx, int vy);
            explicit Shot(json shot);
            NLOHMANN_DEFINE_TYPE_INTRUSIVE(Shot,
                                           rect.x,
                                           rect.y,
                                           vx,
                                           vy);
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
            bool isOpen = false; /*!< Whether or not the door is open */
            std::string leadsTo = ""; /*!< Where the door leads to */

            NLOHMANN_DEFINE_TYPE_INTRUSIVE(Door,
                                           rect.x,
                                           rect.y,
                                           isOpen,
                                           leadsTo);
    };

    class Room {
        public:
            std::string name = ""; /*!< Room name */
            std::vector<Block> blocks; /*!< Vector of Block objects */
            std::vector<Door> doors; /*!< Vector of Door objects */
            std::vector<Metroid> metroids; /*!< Vector of Metroid objects */
            MorphingBall *morphingball = nullptr; /*!< Morphing Ball pointer */
            MotherBrain *motherbrain = nullptr; /*!< MotherBrain pointer */

            NLOHMANN_DEFINE_TYPE_INTRUSIVE(Room, name, blocks, doors, metroids);
    };

}

#endif
