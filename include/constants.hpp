#ifndef METROID_CONSTANTS_H
#define METROID_CONSTANTS_H

#include <string>

namespace EntityCodes {
    const char block = '#';
    const char door = 'D';
    const char empty = ' ';
    const char metroid = 'X';
    const char morphingball = 'B';
    const char motherbrain = 'M';
    const char samus = 'S';
}

namespace MetroidMovement {
    const int mass = 10000;
    const int horizontalStep = 10;
    const int elasticConstant = 100;
    const int dampingConstant = 20;
}

namespace Screen {
    const int width = 640;
    const int height = 480;
}

namespace SamusMovement {
    const int horizontalStep = 10;
    const int initialVerticalVelocity = 10;
    const std::string aimingUpState = "aimingUp";
    const std::string idleState = "idle";
    const std::string jumpingState = "jumping";
    const std::string morphedState = "morphed";
    const std::string runningState = "running";
}

namespace Shooting{
    const std::string shootingState = "shooting";
}

namespace Physics {
    const int gravity = 2;
    const int time = 1;
}

namespace Room {
    const std::string texturesFile = "texture_filenames.txt";
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
