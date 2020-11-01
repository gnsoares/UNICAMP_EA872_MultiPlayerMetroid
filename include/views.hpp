#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class View{
    private:
        const int altura = 400;
        const int largura = 400;
        SDL_Window *window = nullptr;
        SDL_Renderer *renderer = nullptr;
        SDL_Texture *texture = nullptr;
        SDL_Rect target;

    public:
        View();
        ~View();

        void setXS(int x);
        int getXS();
        void setYS(int y);
        int getYS();
        SDL_Rect getTarget();

        const int getAltura();
        const int getLargura();

        void imprimirCoordenadas();
        void draw();
};