#ifndef METROID_CONSTANTS_H
#define METROID_CONSTANTS_H

#include <string>

namespace Entities {
    class Entity {
        public:
            char codeChar;
            std::string code;
            std::string textureFileName;
            Entity(std::string code, std::string textureFileName) {
                this->code = code;
                this->codeChar = code[0];
                this->textureFileName = textureFileName;
            }
    };

    const Entity block("#", "block.jpg");
    const Entity door("D", "door.png");
    const Entity empty(" ", "");
    const Entity metroid("X", "metroid.png");
    const Entity morphingball("B", "morphinball.png");
    const Entity motherbrain("M", "motherbrain.png");
    const Entity samus("S", "samus.png");
    const Entity shot("", "bullet.png");
}

namespace MetroidConstants {
    const int mass = 1000;
    const int elasticConstantX = 500;
    const int elasticConstantY = 300;
    const int maxVx = 9;
    const int maxVy = 6;

    const int initialHP = 20;
    const int damage = 10;
}

namespace Screen {
    const int width = 640;
    const int height = 240;
}

namespace SamusConstants {
    const int horizontalStep = 10;
    const int jumpVy = -18;
    const int gravity = 2;

    const int initialHP = 100;
    const int shotDamage = 5;

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
