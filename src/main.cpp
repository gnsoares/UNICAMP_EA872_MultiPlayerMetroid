#define DEBUG 0

#include "constants.hpp"
#include "controllers.hpp"
#include "models.hpp"
#include "utils.hpp"


#if DEBUG
#include <iostream>
void runTests() {
    Models::Samus samus(5, 7, 10, 13);
    Controllers::Samus samusController(samus);
    Models::Metroid metroid(6, 3, 7, 5);

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
}
#endif


int main() {

    #if DEBUG
    runTests();
    #endif

    Models::Samus samus(Screen::width/2, Screen::height/2, 20, 60);
    Controllers::Samus samusController(samus);
    std::map<std::string, std::string> textureMap = decodeTextures(Room::texturesFile);
    samus.textureFile = textureMap["S"];
    Models::Room testRoom = loadRoom("test", textureMap);

    Controllers::Map map(testRoom, samus);
    map.changeRooms(testRoom);

    SDL_Event event;

    // Game must run until user quits
    while (true) {

        // Poll events
        if (SDL_PollEvent(&event)) {

            // User asked to quit: quit
            if (event.type == SDL_QUIT)
                break;

        }

        samusController.update();
        map.update();
        SDL_Delay(50);

    }

    return 0;
}
