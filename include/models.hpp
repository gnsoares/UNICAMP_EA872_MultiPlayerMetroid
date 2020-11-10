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
            int hp = 100; /*!< Samus' hp */
            int missileCounter;
            int mass;
            int verticalVelocity; /*!< Samus' velocity*/
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
    };

    class ShotVector{
        private:
        public:
            std::vector<Shot>bullets;

            /*! \brief Creates a new instance of the object Shot on a vector
            *
            * Receives the atributes of an object defined by the Shot class
            * and allocated this object on a vector
            * 
            * \param rectx position x of the object
            * \param rectx position y of the object
            * \param rectw width of the object
            * \param recth height of the object
            * \return nothing
            */
            void addShot(int rectx, int recty, int rectw, int recth);

            /*! \updates the value of an already instantiated Shot object
            *
            * Receives a Shot object and uses it to updated the Shot object
            * previouly allocated at the position i of the vector
            *  
            * \param texture
            * \param i position of the object in the vector
            * \return nothing
            */
            void updateShot(Models::Shot shot, int i); //MUDAR AQUI

            /*! \brief erases a Shot object at the position i of a vector
            *  
            * \param i position of the object on the vector
            * \return nothing
            */
            void eraseShot(int i);

            /*! \brief Position of a Shot object
            *  
            * \param i position of the object in the vector
            * \return the position x of the Shot object allocated on the position i of the vector
            */
            Shot returnShotX(int i);

            /*! \brief lenght of vector of Shot objects
            *  
            * \param does not have paramethers
            * \return lenght of vector of Shot objects
            */
            int returnLenghtShot();
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
            std::string state;

            void addMetroid(int rectx, int recty, int rectw, int recth);
            void updateMetroidPosition(int rectx, int i);
            void updateMetroidForce(int fm, int i);
            void updateMetroidAcc (int a, int i);
            void updateMetroidVel (int v, int i);
            void updateMetroidLife(int hp, int i);
            void eraseMetroid(int i);
            void modifyTexture (SDL_Texture *texture, int i);
            Metroid returnMetroid(int i);
            int returnLenghtMetroid();
    };
};

#endif
