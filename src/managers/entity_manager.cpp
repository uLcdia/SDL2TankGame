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
    PlayerParser playerParser("assets/levels/level1/player.json");
    if (!playerParser.parse()) {
        std::cerr << "Failed to parse player config file: " << "assets/levels/level1/player.json" << std::endl;
        return false;
    }

    // Load projectile info
    for (const auto& projectileType : playerParser.getProjectileTypes()) {
        m_resourceManager.addProjectileInfo(projectileType.name, projectileType);
        m_resourceManager.loadProjectileTexture(projectileType.name, projectileType.texturePath);
    }

    auto [tankX, tankY] = playerParser.getPosition();
    createPlayerTank(tankX * mapParser.getTileSize(), tankY * mapParser.getTileSize(), playerParser.getAngle(), playerParser.getScale());

    // Load cartridges
    for (const auto& cartridgeInfo : playerParser.getCartridges()) {
        m_playerTank->addCartridge(cartridgeInfo.name, cartridgeInfo.projectileType, cartridgeInfo.capacity, cartridgeInfo.fireInterval, cartridgeInfo.reloadInterval);
    }

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

void EntityManager::createPlayerTank(double x, double y, double angle, double scale) {
    const auto& chassisTextureInfo = m_resourceManager.getTextureInfo("tank");
    const auto& turretTextureInfo = m_resourceManager.getTextureInfo("turret");
    m_playerTank = std::make_unique<Tank>(x, y, angle, chassisTextureInfo, turretTextureInfo, scale);
}

void EntityManager::createProjectile(const std::string& type, double x, double y, double angle, double scale) {
    const auto& projectileInfo = m_resourceManager.getProjectileInfo(type);
    const auto& textureInfo = m_resourceManager.getTextureInfo(type);
    m_projectiles.push_back(std::make_unique<Projectile>(x, y, angle, textureInfo, scale, projectileInfo.speed, projectileInfo.damage));
}

void EntityManager::update(double deltaTime) {
    if (m_playerTank) {
        m_playerTank->update(deltaTime);
    }

    for (auto it = m_projectiles.begin(); it != m_projectiles.end();) {
        (*it)->update(deltaTime);
        if (!(*it)->isActive()) {
            it = m_projectiles.erase(it);
        } else {
            ++it;
        }
    }
}

void EntityManager::handlePlayerFire() {
    if (m_playerTank) {
        auto fireCallback = [this](const std::string& projectileType, double x, double y, double angle, double scale) {
            this->createProjectile(projectileType, x, y, angle, scale);
        };
        m_playerTank->fire(fireCallback);
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

    // Render projectiles
    for (const auto& projectile : m_projectiles) {
        projectile->render(renderer);
    }
}
