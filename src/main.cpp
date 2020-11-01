#include <iostream>
#include "samusController.hpp"

int main() {
    Samus samus;
    View view;
    SamusPhysics samusphysics(samus, view);

    SDL_Event evento;

    bool rodando = true;

    while(rodando){
        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_QUIT) {
                rodando = false;
            }
        }
        samusphysics.update();
        SDL_Delay(30);
    }
}