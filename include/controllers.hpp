#ifndef METROID_CONTROLLERS_H
#define METROID_CONTROLLERS_H

#include <memory.h>
#include <SDL2/SDL.h>
#include "models.hpp"

namespace Controllers {

    class Metroid{
        private:
            Models::Metroid metroid;
        public:
            Metroid(Models::Metroid &metroid);
            void moleForce();
            void acceleration();
            void velocity();
            void position();
            void uniformMovement();
    };

    class Samus{
        private:
            const Uint8* state;
            Models::Samus samus;
        public:
            Samus(Models::Samus &samus);
            void jumpingAceleration();
            void jumpingPosition();
            void walking();
            void update();
    };
}

#endif
