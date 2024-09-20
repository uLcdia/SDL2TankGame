#ifndef TEXTURE_INFO_H
#define TEXTURE_INFO_H

#include <SDL.h>

struct TextureInfo {
    SDL_Texture* texture;
    int width;
    int height;
};

#endif // TEXTURE_INFO_H