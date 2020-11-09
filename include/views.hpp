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
            void drawFrame(Models::Room &room, Models::Samus &samus);
            void destroyTextures(Models::Room &room);
            void initializeRoom(Models::Room &room, Models::Samus &samus);
            Map();
            ~Map();
    };

}

#endif
