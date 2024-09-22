#include "entity_manager.h"
#include <filesystem>
#include <iostream>

EntityManager::EntityManager(ResourceManager& resourceManager)
    : m_resourceManager(resourceManager), m_playerTank(nullptr)
{}

bool EntityManager::loadLevel(const std::string& level) {
    std::string mapFilePath = "assets/levels/" + level + "/map.json";
    std::string tanksFilePath = "assets/levels/" + level + "/tanks.json";
    std::string projectilesFilePath = "assets/levels/" + level + "/projectiles.json";
    return loadMap(mapFilePath) && loadTanks(tanksFilePath) && loadProjectiles(projectilesFilePath);
}

bool EntityManager::loadMap(const std::string& mapFilePath) {
    MapParser mapParser(mapFilePath);
    if (!mapParser.parse()) {
        std::cerr << "Failed to parse map file: " << mapFilePath << std::endl;
        return false;
    }

    std::cout << "Map parsed successfully." << std::endl;

    // Load background
    m_resourceManager.loadTexture("background", mapParser.getBackgroundTexture());
    
    // Load map textures
    const auto& tileProperties = mapParser.getTileProperties();
    
    for (const auto& [key, tileProperty] : tileProperties) {
        m_resourceManager.loadTexture(tileProperty.name, tileProperty.texturePath);
    }

    loadMapTiles(mapParser);

    std::cout << "Created bricks: " << m_bricks.size() << std::endl;
    std::cout << "Created ground tiles: " << m_groundTiles.size() << std::endl;

    return true;
}

void EntityManager::loadMapTiles(MapParser& mapParser) {
    const auto& layout = mapParser.getMapLayout();
    const auto& tileProperties = mapParser.getTileProperties();
    m_tileSize = mapParser.getTileSize();

    for (std::size_t y = 0; y < layout.size(); ++y) {
        for (std::size_t x = 0; x < layout[y].size(); ++x) {
            char tileChar = layout[y][x];
            auto it = tileProperties.find(tileChar);
            if (it != tileProperties.end() && tileChar != '.') {
                auto& tileProperty = it->second;
                double posX = x * m_tileSize;
                double posY = y * m_tileSize;
                createTile(posX, posY, tileProperty);
            }
        }
    }
}

void EntityManager::createTile(double x, double y, const TileProperty& tileProperty) {
    auto textureInfo = m_resourceManager.getTextureInfo(tileProperty.name);
    if (tileProperty.isBrick) {
        m_bricks.emplace_back(std::make_unique<Brick>(x, y, std::move(textureInfo), tileProperty.health, tileProperty.isVulnerable));
    } else {
        m_groundTiles.emplace_back(std::make_unique<GroundTile>(x, y, std::move(textureInfo)));
    }
    std::cout << "Created " + tileProperty.name + " at (" << x << ", " << y << ")" << std::endl;
}

bool EntityManager::loadTanks(const std::string& tanksFilePath) {
    TankParser tankParser(tanksFilePath);
    if (!tankParser.parse()) {
        std::cerr << "Failed to parse tank file: " << tanksFilePath << std::endl;
        return false;
    }

    // Load player tank
    const auto& playerTankProperty = tankParser.getPlayerTank();
    m_playerTank = createTank(playerTankProperty);

    // Load enemy tanks
    for (const auto& enemyTankProperty : tankParser.getEnemyTanks()) {
        m_enemyTanks.emplace_back(createTank(enemyTankProperty));
    }

    return true;
}

std::unique_ptr<Tank> EntityManager::createTank(const TankProperty& tankProperty) {
    m_resourceManager.loadTexture(tankProperty.chassis.name, tankProperty.chassis.texturePath);
    m_resourceManager.loadTexture(tankProperty.turret.name, tankProperty.turret.texturePath);

    double x = tankProperty.position.first * m_tileSize;
    double y = tankProperty.position.second * m_tileSize;

    auto chassisTexture = m_resourceManager.getTextureInfo(tankProperty.chassis.name);
    auto turretTexture = m_resourceManager.getTextureInfo(tankProperty.turret.name);

    auto tank = std::make_unique<Tank>(tankProperty, x, y, chassisTexture, turretTexture);

    for (const auto& cartridge : tankProperty.cartridges) {
        tank->addCartridge(cartridge);
    }

    return tank;
}

bool EntityManager::loadProjectiles(const std::string& projectilesFilePath) {
    ProjectileParser projectileParser(projectilesFilePath);
    if (!projectileParser.parse()) {
        std::cerr << "Failed to parse projectile file: " << projectilesFilePath << std::endl;
        return false;
    }

    for (const auto& projectile : projectileParser.getProjectiles()) {
        m_projectileProperties.emplace(projectile.name, projectile);
        m_resourceManager.loadTexture(projectile.name, projectile.texturePath);
    }
    return true;
}

void EntityManager::createProjectile(const std::string& type, double x, double y, double angle) {
    const auto& projectileInfo = m_projectileProperties.at(type);
    auto textureInfo = m_resourceManager.getTextureInfo(type);
    m_projectiles.emplace_back(std::make_unique<Projectile>(projectileInfo, x, y, angle, std::move(textureInfo)));
}

void EntityManager::update(double deltaTime) {
    if (m_playerTank) {
        m_playerTank->update(deltaTime);
    }

    for (auto& enemyTank : m_enemyTanks) {
        enemyTank->update(deltaTime);
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
        auto fireCallback = [this](const std::string& projectileType, double x, double y, double angle) {
            this->createProjectile(projectileType, x, y, angle);
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

    // Render enemy tanks
    for (const auto& enemyTank : m_enemyTanks) {
        enemyTank->render(renderer);
    }

    // Render projectiles
    for (const auto& projectile : m_projectiles) {
        projectile->render(renderer);
    }
}
