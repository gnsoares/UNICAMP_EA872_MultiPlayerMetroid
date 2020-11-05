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

/*! \brief Textures decoder
 *
 * \param name textures encoder file name
 * \return map from entity code to texture file name
 */
std::map<std::string, std::string> decodeTextures(std::string name);

/*! \brief Room loader
 *
 * \param name room file name
 * \param textureMap map from entity code to texture file name
 * \return room object
 */
Models::Room loadRoom(std::string name, std::map<std::string, std::string> textureMap);

#endif
