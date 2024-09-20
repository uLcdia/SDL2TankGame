#include "entity_manager.h"
#include <filesystem>
#include <iostream>

EntityManager::EntityManager(ResourceManager& resourceManager)
    : m_resourceManager(resourceManager), m_playerTank(nullptr)
{}

bool EntityManager::loadMap(const std::string& mapFilePath) {
    MapParser mapParser(mapFilePath);
    if (!mapParser.parse()) {
        std::cerr << "Failed to parse map file: " << mapFilePath << std::endl;
        return false;
    }

    std::cout << "Map parsed successfully." << std::endl;

    // Load background
    m_resourceManager.loadBackground(mapParser.getBackgroundTexture());
    
    // Load map textures
    m_resourceManager.loadMapTextures(mapParser);

    loadMapTiles(mapParser);

    std::cout << "Created bricks: " << m_bricks.size() << std::endl;
    std::cout << "Created ground tiles: " << m_groundTiles.size() << std::endl;

    // Create player tank
    auto [tankX, tankY] = mapParser.getPlayerTankPosition();
    createPlayerTank(tankX * mapParser.getTileSize(), tankY * mapParser.getTileSize());

    return true;
}

void EntityManager::loadMapTiles(MapParser& mapParser) {
    const auto& layout = mapParser.getMapLayout();
    const auto& tileProperties = mapParser.getTileProperties();
    const auto tileSize = mapParser.getTileSize();

    for (std::size_t y = 0; y < layout.size(); ++y) {
        for (std::size_t x = 0; x < layout[y].size(); ++x) {
            char tileChar = layout[y][x];
            auto it = tileProperties.find(tileChar);
            if (it != tileProperties.end() && tileChar != '.') {
                auto& tileProperty = it->second;
                double posX = x * tileSize;
                double posY = y * tileSize;
                createTile(posX, posY, tileProperty);
            }
        }
    }
}

void EntityManager::createTile(double x, double y, const TileProperty& tileProperty) {
    const auto& textureInfo = m_resourceManager.getTextureInfo(tileProperty.name);
    if (tileProperty.isBrick) {
        m_bricks.push_back(std::make_unique<Brick>(x, y, textureInfo, tileProperty.health, tileProperty.isVulnerable));
    } else {
        m_groundTiles.push_back(std::make_unique<GroundTile>(x, y, textureInfo));
    }
    std::cout << "Created " + tileProperty.name + " at (" << x << ", " << y << ")" << std::endl;
}

void EntityManager::createPlayerTank(double x, double y) {
    const auto& chassisTextureInfo = m_resourceManager.getTextureInfo("tank");
    const auto& turretTextureInfo = m_resourceManager.getTextureInfo("turret");
    const auto& shellTextureInfo = m_resourceManager.getTextureInfo("shell");
    m_playerTank = std::make_unique<Tank>(x, y, chassisTextureInfo, turretTextureInfo, shellTextureInfo);
}

void EntityManager::createShell(double x, double y, double angle) {
    const auto& shellTextureInfo = m_resourceManager.getTextureInfo("shell");
    m_shells.push_back(std::make_unique<Shell>(x, y, angle, shellTextureInfo));
}

void EntityManager::update(double deltaTime) {
    if (m_playerTank) {
        m_playerTank->update(deltaTime);
    }

    for (auto it = m_shells.begin(); it != m_shells.end();) {
        (*it)->update(deltaTime);
        if (!(*it)->isActive()) {
            it = m_shells.erase(it);
        } else {
            ++it;
        }
    }
}

void EntityManager::render(SDL_Renderer* renderer) const {
    // Render ground tiles
    for (const auto& groundTile : m_groundTiles) {
        groundTile->render(renderer);
    }

    // Render bricks
    for (const auto& brick : m_bricks) {
        brick->render(renderer);
    }

    // Render player tank
    if (m_playerTank) {
        m_playerTank->render(renderer);
    }

    // Render shells
    for (const auto& shell : m_shells) {
        shell->render(renderer);
    }
}
