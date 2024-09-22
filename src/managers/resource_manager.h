#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "../utils/texture_info.h"
#include <SDL.h>
#include <unordered_map>
#include <string>
#include <memory>

class ResourceManager {
public:
    void init(SDL_Renderer* renderer);
    void loadTexture(const std::string& textureName, const std::string& path);
    std::shared_ptr<TextureInfo> getTextureInfo(const std::string& name) const;

private:
    SDL_Renderer* m_renderer;
    std::unordered_map<std::string, TextureInfo> m_textures;
};

#endif // RESOURCE_MANAGER_H