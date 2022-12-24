#include "dados.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

float Dados::getX() {return X;}

void Dados::setY(float y) {Y=y;}

float Dados::getY() {return Y;}

void Dados::setV(float v) {V = v;}

float Dados::getV() {return V;}

void Dados::setFm(float fm) {Fm = fm;}

float Dados::getFm() {return Fm;}

void Dados::setFa(float fa) {Fa = fa;}

float Dados::getFa() {return Fa;}

void Dados::setFt(float ft) {Ft = ft;}

float Dados::getFt() {return Ft;}

void Dados::setA(float a) {A = a;}

float Dados::getA() {return A;}

float Dados::getK() {return K;}

float Dados::getB() {return B;}

float Dados::getM() {return m;}

float Dados::getT() {return T;}

void Dados::imprimir() {std::cout << A << ' ' << V << ' ' << Y << std::endl;}


