#define DEBUG 0

#include "constants.hpp"
#include "controllers.hpp"
#include "models.hpp"
#include "utils.hpp"

#include <iostream>
#if DEBUG
void runTests() {
    Models::Samus samus(5, 7);
    Models::Metroid metroid(6, 3);

    std::cout << "Samus e Metroid devem colidir" << std::endl;
    std::cout << "Estao colidindo? " << checkCollision(samus.rect, metroid.rect) << std::endl;

    std::cout << "Testando importacao de constantes" << std::endl;
    std::cout << "Passo horizontal da Samus " << SamusConstants::horizontalStep << std::endl;

    std::cout << "Testando criação de salas" << std::endl;
    Models::Room testRoom = loadRoom("test");
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

    SDL_Window *window = loadWindow();
    SDL_Renderer *renderer = loadRenderer(window);

    Models::Samus samus(Screen::width/2, Screen::height/2);
    Views::Samus samusView(window, renderer);
    Controllers::Samus samusController(samus, samusView);

    std::vector<Models::Shot> shots;
    Views::Shots shotsView(window, renderer);
    Controllers::Shots shotsController(shots, shotsView);

    Models::Room testRoom = loadRoom("test");
    Views::Map mapView(window, renderer);
    Controllers::Map map(testRoom, mapView);

    SDL_Event event;

    // Game must run until user quits
    while (true) {

        // Poll events
        if (SDL_PollEvent(&event)) {

            // User asked to quit: quit
            if (event.type == SDL_QUIT)
                break;

        }

        SDL_RenderClear(renderer);

        samusController.update();
        shotsController.update(
            samus.rect.x + samus.rect.w/2,
            samus.rect.y + samus.rect.h/2,
            2 * samus.xSight * SamusConstants::horizontalStep,
            2 * samus.ySight * SamusConstants::horizontalStep
        );
        map.update();

        SDL_RenderPresent(renderer);

        SDL_Delay(150);

    }

    unloadSDL(window, renderer);

    return 0;
}
