#include <memory>
#include "view.hpp"
#include "dados.hpp"
#include <SDL2/SDL.h>

class Equacoes{
    private:
        std::shared_ptr<Dados>d;
        std::shared_ptr<View>v;
        const Uint8* state; // estado do teclado

        public:
                Equacoes(std::shared_ptr<Dados>d, std::shared_ptr<View>v){
                        this->d = d;
                        this->v = v;
                        this->state = SDL_GetKeyboardState(nullptr);
                }
                void ForcaMola();
                void ForcaAmortecedor();
                void ForcaTotal(float Fext);
                void Aceleracao();
                void Posicao();
                void Velocidade();
                void Rasterizacao();
                void update();
};
