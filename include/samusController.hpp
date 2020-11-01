#include <memory.h>
#include <SDL2/SDL.h>
#include "models.hpp"
#include "views.hpp"

class SamusPhysics{
    private:
        const Uint8* state;
        Samus samus;
        View view;
    public:
        SamusPhysics(Samus &samus, View &view){
            this->state = SDL_GetKeyboardState(nullptr);
        }
        void jumpingAceleration();
        void jumpingPosition();
        void walking();
        void rasterize();
        void update();
};

