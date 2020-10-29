#include <memory.h>
#include <SDL2/SDL.h>
#include "models.hpp"
#include "views.hpp"

//Incluir .hpp das classes model e view

//Movimento massa-mola
class EnemiesMole{
    private:
       Model model;
       View view;
    public:
    //Atualizar nome das classes dentro do construtor
        EnemiesMole(Model &model, View &view){}

        void ForcaMola();
        void Aceleracao();
        void Velocidade();
        void Posicao();
        void Rasterizacao();
};

//Movimento MU
class EnemiesMU{
    private:
       Model model;
       View view;
    public:
    //Atualizar nome das classes dentro do construtor
        EnemiesMU(Model &model, View &view){}

        void Posicao();

};