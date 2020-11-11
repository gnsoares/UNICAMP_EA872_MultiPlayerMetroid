#ifndef METROID_UTILS_H
#define METROID_UTILS_H

#include <map>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "models.hpp"


/*! \brief Collision checker between two rectangles
 *
 * \param rect1 First rectangle
 * \param rect2 Second rectangle
 * \return Whether or not the rectangles are colliding
 */
bool checkCollision(SDL_Rect rect1, SDL_Rect rect2);

/*! \brief Room loader
 *
 * \param name room file name
 * \param textureMap map from entity code to texture file name
 * \return room object
 */
Models::Room loadRoom(std::string name);

/*! \brief Creates window
 *
 * Creates windows and, if window creation fails,
 * prints erro on the screen
 * 
 * \param does no have any paramethers
 * \return window
 */
SDL_Window *loadWindow();

/*! \brief Creates renderer
 *
 * Creates renderer and, if renderer creation fails,
 * prints error on the screen
 * 
 * \param pointer to window
 * \return renderer
 */
SDL_Renderer *loadRenderer(SDL_Window *window);


/*! \brief Desallocates renderer and window
 * 
 * \param pointer to window
 * \param pointer to renderer
 * \return renderer
 */
void unloadSDL(SDL_Window *window, SDL_Renderer *renderer);

#endif
