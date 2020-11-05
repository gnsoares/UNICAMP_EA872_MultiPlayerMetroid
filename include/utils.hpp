#ifndef METROID_UTILS_H
#define METROID_UTILS_H

#include <SDL2/SDL.h>
#include <map>
#include <string>
#include <vector>
#include "models.hpp"


/*! \brief Collision checker between two rectangles
 *
 * \param rect1 First rectangle
 * \param rect2 Second rectangle
 * \return Whether or not the rectangles are colliding
 */
bool checkCollision(SDL_Rect rect1, SDL_Rect rect2);

/*! \brief Textures decoder
 *
 * \param name textures code file name
 * \return map from char to file name
 */
std::map<std::string, std::string> decodeTextures(std::string name);

/*! \brief Room loader
 *
 * \param name room file nmae
 * \return room object
 */
Models::Room loadRoom(std::string name, std::map<std::string, std::string> textureMap);

#endif
