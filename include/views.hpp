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
            /*! \brief Map view's constructor
            *
            * \param a pointer to a window
            * \param a pointer to a renderer
            * \return nothing
            */
            Map(SDL_Window *window, SDL_Renderer *renderer);

            /*! \brief Render objects on the screen
            *  
            *   Takes objects' positions and renders their respective
            *   textures at that position
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

            /*! \brief Initializes Room
            * 
            *   Gets objects' initial positions and loads their respective textures
            * 
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
