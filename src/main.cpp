#include <chrono>
#include "constants.hpp"
#include "controllers.hpp"
#include "models.hpp"
#include "utils.hpp"


int main() {

    // time control variable
    std::chrono::duration<double> elapsed;

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

        // fetch start of game iteration
        auto start = std::chrono::system_clock::now();

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
            1.5 * samus.xSight * SamusConstants::horizontalStep,
            1.5 * samus.ySight * SamusConstants::horizontalStep
        );
        map.update(shots);

        // render scene
        SDL_RenderPresent(renderer);

        // fetch end of game iteration
        auto end = std::chrono::system_clock::now();

        // measure time duration of game iteration
        elapsed = end - start;

        // control FPS
        SDL_Delay(35 - elapsed.count());

    }

    // stop SDL
    unloadSDL(window, renderer);

    return 0;
}
