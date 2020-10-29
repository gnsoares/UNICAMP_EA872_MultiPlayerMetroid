#include <iostream>
#include "enemiesController.hpp"
#include <memory>
#include <SDL2/SDL.h>

void EnemiesMole::ForcaMola(){
    float fmNovo;
    fmNovo = -model.K*model.yE;
    model.Fm = fmNovo;
}

void EnemiesMole::Aceleracao(){
    float aNovo;
    aNovo = (model.Fm)/model.massaE;
    model.A = aNovo;
}

void EnemiesMole::Velocidade(){
    float vNovo;
    vNovo = model.V+model.A*model.T;
    model.V = vNovo;
}
        
void EnemiesMole::Posicao(){
    float yNovo;
    yNovo = model.yE+model.V*model.T;
    model.yE = yNovo;
}

void EnemiesMole::Rasterizacao(){
    int xPixel = model.xE + view.larguraTela/2;
    int yPixel = model.yE + view.alturaTela/2;
    view.xE = xPixel;
    view.yE = xPixel;
}

void EnemiesMU::Posicao(){
    int xNovo = model.xMU-model.vMU*model.T;
    model.xMU = xNovo;
    /*Se bater no fim da tela, inverte sentido: int xNovo = model.xMU+model.vMU*model.T;
    model.xMU = xNovo;*/
}

