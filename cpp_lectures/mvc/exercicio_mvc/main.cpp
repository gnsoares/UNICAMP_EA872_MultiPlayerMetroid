#include <iostream>
#include <memory>
#include "controller.hpp"
#include <SDL2/SDL.h>

int main() {
	std::shared_ptr<View>v (new View);
	std::shared_ptr<Dados>d (new Dados);
	std::shared_ptr<Equacoes>e (new Equacoes(d,v));

    SDL_Event evento; // eventos discretos

    // Controlador:
    bool rodando = true;

    // Laco principal do jogo
    while(rodando) {

        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_QUIT) {
                rodando = false;
            }
        }

    e->update();

    // Delay para diminuir o framerate
    SDL_Delay(30);
  }

}

