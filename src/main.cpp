#include "constants.hpp"
#include "controllers.hpp"
#include "models.hpp"
#include "utils.hpp"


int main() {

    // SDL visualization variables
    SDL_Window *window = loadWindow();
    SDL_Renderer *renderer = loadRenderer(window);

    // Samus
    Models::Samus samus(Screen::width/2, Screen::height/2);
    Views::Samus samusView(window, renderer);
    Controllers::Samus samusController(samus, samusView);

    // Shots
    std::vector<Models::Shot> shots;
    Views::Shots shotsView(window, renderer);
    Controllers::Shots shotsController(shots, shotsView);

    // Map
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

        // clear scene
        SDL_RenderClear(renderer);

        // update all members
        samusController.update(testRoom.blocks, testRoom.doors, testRoom.metroids);
        shotsController.update(
            samus.rect.x + samus.rect.w/2,
            samus.rect.y + samus.rect.h/2,
            2 * samus.xSight * SamusConstants::horizontalStep,
            2 * samus.ySight * SamusConstants::horizontalStep
        );
        map.update(shots);

        // render scene
        SDL_RenderPresent(renderer);

        // control FPS
        SDL_Delay(50);

    }

    // stop SDL
    unloadSDL(window, renderer);

    return 0;
}
