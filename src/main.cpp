#include <iostream>
#include "constants.hpp"
#include "models.hpp"
#include "utils.hpp"

int main() {

    Samus samus(5, 7);
    samus.rect.w = 10;
    samus.rect.h = 13;

    Metroid metroid(6, 3);
    metroid.rect.w = 7;
    metroid.rect.h = 5;

    std::cout << "Testando retangulo da Samus" << std::endl;
    std::cout << "(x = " << samus.rect.x << ", y = " << samus.rect.y << ")" << std::endl;
    std::cout << samus.rect.w << " x " << samus.rect.h << std::endl;

    std::cout << "Testando retangulo do Metroid" << std::endl;
    std::cout << "(x = " << metroid.rect.x << ", y = " << metroid.rect.y << ")" << std::endl;
    std::cout << metroid.rect.w << " x " << metroid.rect.h << std::endl;

    std::cout << "Samus e Metroid devem colidir" << std::endl;
    std::cout << "Estao colidindo? " << checkCollision(samus.rect, metroid.rect) << std::endl;

    std::cout << "Testando importacao de constantes" << std::endl;
    std::cout << "Passo horizontal da Samus " << SamusMovement::horizontalStep << std::endl;

    return 0;
}
