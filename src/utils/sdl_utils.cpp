#include "sdl_utils.h"
#include <SDL_image.h>
#include <iostream>

// Initialize SDL, create window and renderer
bool initSDL(SDL_Window*& window, SDL_Renderer*& renderer, const char* title, int width, int height) {
    // Initialize SDL video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create window
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Create renderer for window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Anti-aliasing
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    return true;
}

// Load texture and its resolution
TextureInfo loadTextureWithInfo(const std::string& path, SDL_Renderer* renderer) {
    TextureInfo info;
    info.texture = nullptr;
    info.width = 0;
    info.height = 0;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        std::cerr << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
    } else {
        info.texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (info.texture == nullptr) {
            std::cerr << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << std::endl;
        }

        info.width = loadedSurface->w;
        info.height = loadedSurface->h;

        SDL_FreeSurface(loadedSurface);
    }

    return info;
}