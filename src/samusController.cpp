#include <iostream>
#include "leisFisicas.hpp"
#include <memory>
#include <SDL2/SDL.h>

void Physics::aceleracaoSalto(){
    dados.velocidadeY = dados.velocidadeInicialY - dados.gravidade*dados.tempo;
}

void Physics::saltoSamus(){
    dados.y = dados.yInicial + dados.velocidadeY*dados.tempo - (dados.gravidade*dados.tempo^2)/2;
    dados.yInicial = dados.y;
}

void Physics::movimentoUniforme(){
    if (//Teclado direita velocidade = +5)
    if (//teclado esquerda )
    dados.x = dados.xInicial + dados.velocidadeX*dados.tempo;
    dados.xInicial = dados.x;
}