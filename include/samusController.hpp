#include <memory.h>
#include <SDL2/SDL.h>
#include "models.hpp"
#include "views.hpp"

class SamusPhysics{
    private:
        const Uint8* state;
        Models::Samus samus;
    public:
        SamusPhysics(Models::Samus &samus) : samus(samus){
            this->state = SDL_GetKeyboardState(nullptr);
        }
        void jumpingAceleration();
        void jumpingPosition();
        void walking();
        void update();
};

