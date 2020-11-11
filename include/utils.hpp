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
 * \return window pointer
 */
SDL_Window *loadWindow();

/*! \brief Creates renderer
 *
 * Creates renderer and, if renderer creation fails,
 * prints error on the screen
 * 
 * \param window pointer to window
 * \return renderer pointer
 */
SDL_Renderer *loadRenderer(SDL_Window *window);


/*! \brief Desallocates renderer and window
 * 
 * \param window pointer to window
 * \param renderer pointer to renderer
 * \return renderer
 */
void unloadSDL(SDL_Window *window, SDL_Renderer *renderer);

#endif
