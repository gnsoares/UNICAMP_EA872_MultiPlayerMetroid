#include <iostream>
#include "controller.hpp"
#include <memory>
#include <SDL2/SDL.h>

void Equacoes::ForcaMola(){
    float Fm_novo;
    Fm_novo = -(d->getK()*d->getY());
    d->setFm(Fm_novo);
}

void Equacoes::ForcaAmortecedor(){
    float Fa_novo;
    Fa_novo = -(d->getB()*d->getV());
    d->setFa(Fa_novo);
}

void Equacoes::ForcaTotal(float Fext){
    float Ft_novo;
    Ft_novo = (d->getFa()+d->getFm() + Fext);
    d->setFt(Ft_novo);
}

void Equacoes::Aceleracao(){
    float A_novo;
    A_novo = (d->getFt()/d->getM());
    d->setA(A_novo);
}

void Equacoes::Velocidade(){
    float V_novo;
    V_novo = (d->getV()+d->getA()*d->getT());
    d->setV(V_novo);
}

void Equacoes::Posicao(){
    float Y_novo;
    Y_novo = (d->getY()+d->getV()*d->getT());
    d->setY(Y_novo);

}

void Equacoes::Rasterizacao(){
    int YPixel = d->getY() + v->getAltura()/2;
    int XPixel = d->getX() + v->getLargura()/2;
    v->setX(XPixel);
    v->setY(YPixel);
}

void Equacoes::update() {

    float Fext = 0;

    // Polling de eventos
    SDL_PumpEvents(); // atualiza estado do teclado
    // if (state[SDL_SCANCODE_LEFT]) v->getTarget()->x -= 1;
    // if (state[SDL_SCANCODE_RIGHT]) v->getTarget()->x += 1;
    if (state[SDL_SCANCODE_UP]) Fext -= 1000;
    if (state[SDL_SCANCODE_DOWN]) Fext += 1000;

    ForcaMola();
    ForcaAmortecedor();
    ForcaTotal(Fext);
    Aceleracao();
    Velocidade();
    Posicao();
    Rasterizacao();

    v->draw();
    v->imprimirCoordenadas();
}
