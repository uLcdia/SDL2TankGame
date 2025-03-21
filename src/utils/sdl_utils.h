#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include "texture_info.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <string>

bool initSDL(SDL_Window*& window, SDL_Renderer*& renderer, const char* title, int width, int height);
TextureInfo loadTextureWithInfo(const std::string& path, SDL_Renderer* renderer);
Mix_Music* loadMixerMusic(const std::string& path);

#endif // SDL_UTILS_H