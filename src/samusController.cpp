#include <iostream>
#include "samusController.hpp"
#include <memory>
#include <SDL2/SDL.h>

void SamusMovements::velocidadeSalto(){
    model.velocidadeY = model.velocidadeInicialY - model.gravidade*model.tempo;
}

void SamusMovements::saltoSamus(){
    model.yS = model.ySInicial + model.velocidadeY*model.tempo - (model.gravidade*model.tempo^2)/2;
    model.ySInicial = model.y;
}

void SamusMovements::movimentoUniforme(){
    //if (teclado direita velocidade = +5)
    model.xS += 0.1;
    //if (teclado esquerda)
    model.xS -= 0.1;
}

void SamusMovements::Rasterizacao(){
    int xPixel = model.xS + view.larguraTela/2;
    int yPixel = model.yS + view.alturaTela/2;
    view.xS = xPixel;
    view.yS = xPixel;
}