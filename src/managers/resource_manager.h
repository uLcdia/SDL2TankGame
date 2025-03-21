#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "../utils/texture_info.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <unordered_map>
#include <string>
#include <memory>

/**
 * @class ResourceManager
 * @brief Manages game resources, particularly textures.
 *
 * This class is responsible for loading, storing, and providing access to
 * game textures.
 */
class ResourceManager {
public:
    void init(SDL_Renderer* renderer);
    void loadTexture(const std::string& textureName, const std::string& path);
    std::shared_ptr<TextureInfo> getTextureInfo(const std::string& name) const;

    void loadMusic(const std::string& musicName, const std::string& path);
    Mix_Music* getMusic(const std::string& name) const;

private:
    SDL_Renderer* m_renderer;
    std::unordered_map<std::string, TextureInfo> m_textures;
    std::unordered_map<std::string, Mix_Music*> m_music;
};

#endif // RESOURCE_MANAGER_H