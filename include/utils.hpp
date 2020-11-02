#include <SDL2/SDL.h>
#include <map>
#include <string>
#include <vector>

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
