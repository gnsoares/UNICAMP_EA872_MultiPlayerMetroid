#ifndef METROID_CONSTANTS_H
#define METROID_CONSTANTS_H

#include <string>

namespace Entities {
    class Entity {
        public:
            char codeChar;
            std::string code; /*!< Characters used to create the room, initially*/
            std::string textureFileName; /*!< Name of the file where the room is created*/
            
            /*! \brief Entity's constructor
            *
            * \param  a string
            * \param a string
            * \return nothing
            */
            Entity(std::string code, std::string textureFileName) {
                this->code = code;
                this->codeChar = code[0];
                this->textureFileName = textureFileName;
            }
    };

    const Entity block("#", "block.jpg"); /*!< Associating block's charactere to its texture*/
    const Entity door("D", "door.png");/*!< Associating door's charactere to its texture*/
    const Entity empty(" ", ""); 
    const Entity metroid("X", "metroid.png"); /*!< Associating Metroid's charactere to its texture*/
    const Entity morphingball("B", "morphinball.png"); /*!< Associating Morphing Ball's charactere to its texture*/
    const Entity motherbrain("M", "motherbrain.png"); /*!< Associating Mother Brain's charactere to its texture*/
    const Entity samus("S", "samus.png"); /*!< Associating Samus' charactere to its texture*/
    const Entity shot("", "bullet.png"); /*!< Associating Shot's charactere to its texture*/
}

namespace MetroidConstants {
    const int mass = 1000; /*!< Metroid's mass*/
    const int elasticConstantX = 500; /*!< Metroid's elastic constant at X axis*/
    const int elasticConstantY = 300; /*!< Metroid's elastic constant at Y axis*/
    const int maxVx = 9; /*!< Metroid's maximum velocity at X axis*/
    const int maxVy = 6;  /*!< Metroid's maximum velocity at Y axis*/

    const int initialHP = 20;  /*!< Metroid's initial life*/
    const int damage = 10;  /*!< Damage caused by Metroid*/
}

namespace Screen {
    const int width = 640;  /*!< Screen width*/
    const int height = 240;  /*!< Screen height*/
}

namespace SamusConstants {
    const int horizontalStep = 10;  /*!< Samus's horizontal step*/
    const int jumpVy = -18;  /*!<  Samus' jump initial velocity*/
    const int gravity = 2;  /*!< Gravity*/

    const int initialHP = 100;  /*!< Samus' initial life*/
    const int shotDamage = 5;  /*!< Damage caused by shot*/
 
    const std::string idleState = "idle";
    const std::string morphedState = "morphed";
    const std::string runningState = "running";
}

namespace Commands {
    const std::string moveLeft = "MVL";
    const std::string moveRight = "MVR";
    const std::string lookUp = "LKU";
    const std::string morph = "MPH";
    const std::string jump = "JMP";
    const std::string shot = "SHT";
}

#endif
