#include <chrono>
#include <SDL2/SDL.h>
#include "controllers.hpp"


int main() {

    // time control variable
    std::chrono::duration<double> elapsed;

    // game controller
    Controllers::Game game;

    // sdl events
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

        // update game state
        game.update();

        // fetch end of game iteration
        auto end = std::chrono::system_clock::now();

        // measure time duration of game iteration
        elapsed = end - start;

        // control FPS
        SDL_Delay(35 - elapsed.count());

    }

    return 0;
}
