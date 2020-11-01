#ifndef METROID_CONSTANTS_H
#define METROID_CONSTANTS_H

namespace SamusCharacteristics{
    const int mass = 70000;
    const int initialHP = 100;
}

namespace SamusMovement {
    const int horizontalStep = 10;
    const int initialVerticalVelocity = 10;
}

namespace MetroidCharacteristics{
    const int mass = 10000;
    const int initialHP = 50;
}

namespace MetroidMovement {
    const int horizontalStep = 10;
    const int elasticConstant = 5;
    const int dampingConstant = 5;
}

namespace Physics{
    const int gravity = 9.8;
    const int time = 0.05;
}

#endif