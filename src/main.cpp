#define DEBUG 0

#include "constants.hpp"
#include "controllers.hpp"
#include "models.hpp"
#include "utils.hpp"

int main() {

    #if DEBUG
    runTests();
    #endif

    Models::Samus samus(Screen::width/2, Screen::height/2-77, 20, 60);
    Models::ShotVector bullets;
    Models::Shot shots (Screen::width/2, Screen::height/2, 10, 20);
    Controllers::Samus samusController(samus);
    Controllers::Shots shotsController(shots, bullets, samus);
    std::map<std::string, std::string> textureMap = decodeTextures(Room::texturesFile);
    samus.textureFile = textureMap["S"];
    Models::Room testRoom = loadRoom("test", textureMap);

    Controllers::Map map(testRoom, samus, bullets);
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
        shotsController.update();
        map.metroidUpdate();
        map.update();
        SDL_Delay(50);

    }

    return 0;
}
