#include <iostream>
#include "constants.hpp"
#include "models.hpp"
#include "utils.hpp"

int main() {

    Models::Samus samus(5, 7);
    samus.rect.w = 10;
    samus.rect.h = 13;

    Models::Metroid metroid(6, 3);
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

    std::cout << "Testando decodificação das texturas" << std::endl;
    std::map<std::string, std::string> map = decodeTextures(Room::texturesFile);
    for (std::map<std::string, std::string>::iterator it = map.begin(); it != map.end(); it++)
        std::cout << it->first << " :: " << it->second << std::endl;

    std::cout << "Testando criação de salas" << std::endl;
    Models::Room testRoom = loadRoom("test", map);
    std::cout << "Blocos: ";
    for (int i = 0; i < testRoom.blocks.size(); i++) {
        std::cout << "(x = " << testRoom.blocks[i].rect.x << ", y = " << testRoom.blocks[i].rect.y << ") ";
    }
    std::cout << std::endl;
    std::cout << "Portas: ";
    for (int i = 0; i < testRoom.doors.size(); i++) {
        std::cout << "(x = " << testRoom.doors[i].rect.x << ", y = " << testRoom.doors[i].rect.y << ") ";
    }
    std::cout << std::endl;

    return 0;
}
