#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include "texture_info.h"
#include <SDL.h>

bool initSDL(SDL_Window*& window, SDL_Renderer*& renderer, const char* title, int width, int height);
SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer);
TextureInfo loadTextureWithInfo(const char* path, SDL_Renderer* renderer);

#endif // SDL_UTILS_H