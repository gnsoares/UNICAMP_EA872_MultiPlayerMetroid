#include <iostream>
#include "constants.hpp"
#include "models.hpp"

int main() {

    Samus samus(5, 7);

    std::cout << "Testando criacao de modelos" << std::endl;
    std::cout << samus.rect.x << ", " << samus.rect.y << std::endl;

    std::cout << "Testando importacao de constantes" << std::endl;
    std::cout << "Passo horizontal da Samus " << SamusMovement::horizontalStep << std::endl;

    return 0;
}