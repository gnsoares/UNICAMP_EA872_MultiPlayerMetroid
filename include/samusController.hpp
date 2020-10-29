#include <memory.h>
#include <SDL2/SDL.h>
//Incluir .hpp das clases para quais os ponteiros apontam

class Physics{
    private:
        std::shared_ptr<Samus>ptr;
        //Terminar de colocar ponteiros apontando pras classes de Model/View
    public:
        Physics(std::shared_ptr<Samus>samus){
            this -> samus = samus;
        }

        //EQUAÇÕES DAS LEIS FÍSICAS

