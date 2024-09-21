#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "../utils/texture_info.h"
#include "../utils/map_parser.h"
#include "../utils/projectile_property.h"
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
    void loadProjectileTexture(const std::string& name, const std::string& path);

    void addProjectileInfo(const std::string& name, const ProjectileProperty& property);
    const ProjectileProperty& getProjectileInfo(const std::string& name) const;

private:
    void loadTexture(const std::string& name, const char* path);
    
    SDL_Renderer* m_renderer;
    std::unordered_map<std::string, TextureInfo> m_textures;
    std::unordered_map<std::string, ProjectileProperty> m_projectileProperties;
};

#endif // RESOURCE_MANAGER_H