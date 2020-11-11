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
             * \param window pointer to a window
             * \param renderer pointer to a renderer
             */
            Map(SDL_Window *window, SDL_Renderer *renderer);

            /*! \brief Render objects on the screen
             *
             * Renders all objetcs in a room
             *
             * \param room room model
             * \return nothing
             */
            void render(Models::Room &room);

            /*! \brief Desallocates textures allocated during the program's execution
             *
             * \param room room model
             * \return nothing
             */
            void destroyTextures(Models::Room &room);

            /*! \brief Initializes Room
             *
             * Loads the textures of all elements in a room
             *
             * \param room room model
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
            /*! \brief Samus view's constructor
             *
             * \param window pointer to a window
             * \param renderer pointer to a renderer
             */
            Samus(SDL_Window *window, SDL_Renderer *renderer);

            /*! \brief Samus texture loader
             *
             * \param samus Samus model
             * \return nothing
             */
            void loadTexture(Models::Samus &samus);

            /*! \brief Renders Samus
             *
             * \param samus Samus model
             * \return nothing
             */
            void render(Models::Samus &samus);

            /*! \brief Process user command
             *
             * \return command string
             */
            std::string processCommand();
    };

    class Shots {
        private:
            SDL_Renderer *renderer = nullptr;
            SDL_Window *window = nullptr;
            const Uint8 *state = SDL_GetKeyboardState(NULL);

        public:
            /*! \brief Shots view's constructor
             *
             * \param window pointer to a window
             * \param renderer pointer to a renderer
             */
            Shots(SDL_Window *window, SDL_Renderer *renderer);

            /*! \brief Shot texture loader
             *
             * \param shot shot model
             * \return nothing
             */
            void loadTexture(Models::Shot &shot);

            /*! \brief Renders shot
             *
             * \param samus shot model
             * \return nothing
             */
            void render(std::vector<Models::Shot> &shots);

            /*! \brief Process user command
             *
             * \return command string
             */
            std::string processCommand();
    };

}

#endif
