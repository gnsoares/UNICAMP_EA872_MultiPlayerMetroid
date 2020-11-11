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
            SDL_Window *window = nullptr;

        public:
            Map(SDL_Window *window, SDL_Renderer *renderer);

            /*! \brief Draws frame
            *  
            *   Receives three models previously allocated, and renderizes
            *   the textures attributed to each end every element shown in
            *   the screen, based on their locations
            *  
            * \param a Model (containing Room's infos)
            * \return nothing
            */
            void render(Models::Room &room);

            /*! \brief Desallocates textures allocated during the program's execution
            * \param a Model (containing Room's infos)
            * \return nothing
            */
            void destroyTextures(Models::Room &room);

            /*! \brief Desallocates textures allocated during the program's execution
            * \param a Model (containing Room's infos)
            * \return nothing
            */
            void initializeRoom(Models::Room &room);
    };

    class Samus {
        private:
            SDL_Renderer *renderer = nullptr;
            SDL_Window *window = nullptr;
            const Uint8 *state = SDL_GetKeyboardState(NULL);

        public:
            Samus(SDL_Window *window, SDL_Renderer *renderer);
            void loadTexture(Models::Samus &samus);
            void render(Models::Samus &samus);

            /*! \brief Return Command
            * \param Return a string that will later indicate
            * what command should be excuted based on the state
            * of the keyboard
            * \return string
            */
            std::string processCommand();
    };

    class Shots {
        private:
            SDL_Renderer *renderer = nullptr;
            SDL_Window *window = nullptr;
            const Uint8 *state = SDL_GetKeyboardState(NULL);

        public:
            Shots(SDL_Window *window, SDL_Renderer *renderer);
            void loadTexture(Models::Shot &shot);
            void render(std::vector<Models::Shot> &shots);

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
