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
    const int horizontalStep = 10;
    const int elasticConstant = 5;
    const int dampingConstant = 5;
}

namespace SamusMovement {
    const int horizontalStep = 10;
    const int initialVerticalVelocity = 10;
}

namespace Physics{
    const int gravity = 1;
    const int time = 1;
}

namespace Room {
    const std::string texturesFile = "texture_filenames.txt";
}

#endif
