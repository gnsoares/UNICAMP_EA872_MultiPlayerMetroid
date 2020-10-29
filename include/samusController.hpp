#include <memory.h>
#include <SDL2/SDL.h>
//Incluir .hpp das classes model e view

class SamusMovements{
    private:
       Model model;
       View view;
    public:
        SamusMovements(Model &model, View &view){
        }

        void velocidadeSalto();
        void saltoSamus();
        void movimentoUniforme();
        void Rasterizacao();
};

class Tiro{

};