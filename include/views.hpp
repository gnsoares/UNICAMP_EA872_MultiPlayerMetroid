#ifndef METROID_VIEWS_H
#define METROID_VIEWS_H

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "models.hpp"

namespace Views {

    class Map {
        private:
            SDL_Renderer *renderer = nullptr;

        public:
            SDL_Window *window = nullptr;
            void drawFrame(Models::Room &room, Models::Samus &samus, Models::ShotVector &bullets);
            void destroyTextures(Models::Room &room);
            void initializeRoom(Models::Room &room, Models::Samus &samus, Models::ShotVector &bullets);
            Map();
            ~Map();
    };

    class Samus {
        private:
            const Uint8 *state = SDL_GetKeyboardState(NULL);

        public:
            std::string processCommand();
    };

    class Shots{
        private:
            const Uint8 *state = SDL_GetKeyboardState(NULL);
        public:
            std::string processCommand();
    };

}

#endif
