#include "resource_manager.h"
#include "../utils/sdl_utils.h"
#include <iostream>

void ResourceManager::init(SDL_Renderer* renderer) {
    m_renderer = renderer;
}

void ResourceManager::loadTexture(const std::string& textureName, const std::string& path) {
    if (m_textures.find(textureName) != m_textures.end()) {
        std::cerr << "Texture already loaded: " << textureName << std::endl;
        return;
    }

    std::string fullPath = "./assets/textures/" + path;
    TextureInfo info = loadTextureWithInfo(fullPath, m_renderer);
    if (info.texture != nullptr) {
        m_textures.emplace(textureName, std::move(info));
        std::cout << "Loaded texture: " << textureName << " (" << info.width << "x" << info.height << ")" << std::endl;
    } else {
        std::cerr << "Failed to load texture: " << textureName << std::endl;
    }
}

std::shared_ptr<TextureInfo> ResourceManager::getTextureInfo(const std::string& name) const {
    return std::make_shared<TextureInfo>(m_textures.at(name));
}

/**
 * Textures used in the game:
 * 
 * Map:
 * https://opengameart.org/content/lots-of-free-2d-tiles-and-sprites-by-hyptosis
 * 
 * Tank:
 * https://opengameart.org/content/tank-top-view
 * 
 * Projectiles:
 * https://opengameart.org/content/bullet-for-ammometer
 * 
 */

void ResourceManager::loadMusic(const std::string& musicName, const std::string& path) {
    if (m_music.find(musicName) != m_music.end()) {
        std::cerr << "Music already loaded: " << musicName << std::endl;
        return;
    }

    std::string fullPath = "./assets/audio/music/" + path;
    Mix_Music* music = loadMixerMusic(fullPath);
    if (music != nullptr) {
        m_music.emplace(musicName, music);
        std::cout << "Loaded music: " << musicName << std::endl;
    } else {
        std::cerr << "Failed to load music: " << musicName << std::endl;
    }
}

Mix_Music* ResourceManager::getMusic(const std::string& name) const {
    auto it = m_music.find(name);
    if (it != m_music.end()) {
        return it->second;
    }
    std::cerr << "Music not found: " << name << std::endl;
    return nullptr;
}