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
            SDL_Texture *texture = IMG_LoadTexture(renderer, "../assets/door.png");

        public:
            SDL_Window *window = nullptr;

            /*! \brief Draws frame
            *  
            *   Receives three models previously allocated, and renderizes
            *   the textures attributed to each end every element shown in
            *   the screen, based on their locations
            *  
            * \param a Model (containing Room's infos)
            * \param a Model (containing Samus' infos)
            * \param a Model (containing vector of Shots infos)
            * \return nothing
            */
            void drawFrame(Models::Room &room, Models::Samus &samus, Models::ShotVector &bullets);

            /*! \brief Desallocates textures allocated during the program's execution
            * \param a Model (containing Room's infos)
            * \return nothing
            */
            void destroyTextures(Models::Room &room);

            /*! \brief Desallocates textures allocated during the program's execution
            * \param a Model (containing Room's infos)
            * \return nothing
            */
            void initializeRoom(Models::Room &room, Models::Samus &samus, Models::ShotVector &bullets);
            Map();
            ~Map();
    };

    class Samus {
        private:
            const Uint8 *state = SDL_GetKeyboardState(NULL);

        public:
            /*! \brief Return Command
            * \param Return a string that will later indicate
            * what command should be excuted based on the state
            * of the keyboard
            * \return string
            */
            std::string processCommand();
    };

    class Shots{
        private:
            const Uint8 *state = SDL_GetKeyboardState(NULL);

        public:
            /*! \brief Return Command
            * \param Return a string that will later indicate
            * what command should be excuted based on the state
            * of the keyboard
            * \return string
            */
            std::string processCommand();
    };

}

#endif
