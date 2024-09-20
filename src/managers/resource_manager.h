#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "../utils/texture_info.h"
#include "../utils/map_parser.h"
#include <SDL.h>
#include <unordered_map>
#include <string>

class ResourceManager {
public:
    void init(SDL_Renderer* renderer);
    SDL_Texture* getTexture(const std::string& name);
    const TextureInfo& getTextureInfo(const std::string& name) const;
    
    void loadBackground(const std::string& backgroundPath);
    void loadMapTextures(const MapParser& mapParser);

private:
    void loadTexture(const std::string& name, const char* path);
    
    SDL_Renderer* m_renderer;
    std::unordered_map<std::string, TextureInfo> m_textures;
};

#endif // RESOURCE_MANAGER_H