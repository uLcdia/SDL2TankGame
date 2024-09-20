#include "resource_manager.h"
#include "../utils/sdl_utils.h"
#include <iostream>
#include <filesystem>

void ResourceManager::init(SDL_Renderer* renderer) {
    m_renderer = renderer;
    
    // https://opengameart.org/content/tank-top-view
    loadTexture("tank", "./assets/textures/entities/vehicles/tank.png");
    loadTexture("turret", "./assets/textures/entities/vehicles/turret.png");

    // https://opengameart.org/content/bullet-for-ammometer
    loadTexture("shell", "./assets/textures/entities/projectiles/shell.png");
}

void ResourceManager::loadTexture(const std::string& name, const char* path) {
    TextureInfo info = loadTextureWithInfo(path, m_renderer);
    if (info.texture != nullptr) {
        m_textures[name] = std::move(info);
        std::cout << "Loaded texture: " << name << " (" << info.width << "x" << info.height << ")" << std::endl;
    } else {
        std::cerr << "Failed to load texture: " << name << std::endl;
    }
}

SDL_Texture* ResourceManager::getTexture(const std::string& name) {
    auto it = m_textures.find(name);
    if (it != m_textures.end()) {
        return it->second.texture;
    }
    return nullptr;
}

const TextureInfo& ResourceManager::getTextureInfo(const std::string& name) const {
    return m_textures.at(name);
}

void ResourceManager::loadBackground(const std::string& backgroundPath) {
    std::string fullPath = "./assets/textures/" + backgroundPath;
    std::string textureName = "background";
    std::cout << "Loading background texture: " << textureName << " from " << fullPath << std::endl;
    loadTexture(textureName, fullPath.c_str());
}

void ResourceManager::loadMapTextures(const MapParser& mapParser) {

    // Textures used in the map:
    // https://opengameart.org/content/lots-of-free-2d-tiles-and-sprites-by-hyptosis

    const auto& tileProperties = mapParser.getTileProperties();
    
    for (const auto& [key, tileProperty] : tileProperties) {
        std::string fullPath = "./assets/textures/" + tileProperty.texture;
        std::string textureName = std::filesystem::path(tileProperty.texture).stem().string();
        std::cout << "Loading texture: " << textureName << " from " << fullPath << std::endl;
        loadTexture(textureName, fullPath.c_str());
    }
}