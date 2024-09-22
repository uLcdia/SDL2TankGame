#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include "texture_info.h"
#include <SDL.h>
#include <string>

bool initSDL(SDL_Window*& window, SDL_Renderer*& renderer, const char* title, int width, int height);
TextureInfo loadTextureWithInfo(const std::string& path, SDL_Renderer* renderer);

#endif // SDL_UTILS_H