#include <memory.h>
#include <SDL2/SDL.h>
#include "models.hpp"
#include "views.hpp"

class MetroidPhysics{
    private:
        Metroid metroid;
    public:
        MetroidPhysics(Metroid &metroid);
        void moleForce();
        void acceleration();
        void velocity();
        void position();
        void uniformMovement();
};