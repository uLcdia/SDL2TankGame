#include "entity_manager.h"
#include <filesystem>
#include <iostream>
#include <limits>

constexpr bool DEBUG_COLLISIONS = true;

EntityManager::EntityManager(ResourceManager& resourceManager)
    : m_resourceManager(resourceManager)
{}

void EntityManager::update(double deltaTime) {
    if (m_playerTank && m_playerTank->isAlive()) {
        handleUpdate(*m_playerTank, deltaTime, true);
    }

    for (auto& enemyTank : m_enemyTanks) {
        if (enemyTank->isAlive()) {
            handleUpdate(*enemyTank, deltaTime, false);
        }
    }

    for (auto it = m_projectiles.begin(); it != m_projectiles.end();) {
        handleUpdate(*(*it), deltaTime);

        if (!(*it)->isActive()) {
            it = m_projectiles.erase(it);
        } else {
            ++it;
        }
    }
}

void EntityManager::render(SDL_Renderer* renderer) const {
    // Render ground tiles
    for (const auto& groundTile : m_groundTiles) {
        groundTile->render(renderer);
        if (DEBUG_COLLISIONS) {
            groundTile->renderEdges(renderer);
        }
    }

    // Render bricks
    for (const auto& brick : m_bricks) {
        if (brick->isAlive()) {
            brick->render(renderer);
            if (DEBUG_COLLISIONS) {
                brick->renderEdges(renderer);
            }
        }
    }

    // Render enemy tanks
    for (const auto& enemyTank : m_enemyTanks) {
        enemyTank->render(renderer);
        if (DEBUG_COLLISIONS) {
            enemyTank->renderEdges(renderer);
        } 
    }

    // Render player tank
    if (m_playerTank) {
        m_playerTank->render(renderer);
        if (DEBUG_COLLISIONS) {
            m_playerTank->renderEdges(renderer);
        }
    }

    // Render projectiles
    for (const auto& projectile : m_projectiles) {
        projectile->render(renderer);
        if (DEBUG_COLLISIONS) {
            projectile->renderEdges(renderer);
        }
    }
}

std::string EntityManager::getTankName(const Tank& tank) const {
    return tank.getName();
}

double EntityManager::getTankHealth(const Tank& tank) const {
    return tank.getHealth();
}

bool EntityManager::getTankIsAlive(const Tank& tank) const {
    return tank.isAlive();
}

void EntityManager::handleTankMovement(Tank& tank, TankMovements::Movement movement) {
    tank.move(movement, getTileSpeedMultiplier(tank));
}

void EntityManager::handleTankRotation(Tank& tank, TankMovements::Rotation rotation) {
    tank.rotate(rotation, getTileSpeedMultiplier(tank));
}

void EntityManager::handleTankTurretRotation(Tank& tank, TankMovements::Rotation rotation) {
    tank.rotateTurret(rotation);
}

void EntityManager::handleTankCycleCartridge(Tank& tank) {
    tank.cycleCartridge();
}

void EntityManager::handleTankFire(Tank& tank) {
    auto fireCallback = [this](const std::string& projectileType, double x, double y, double angle, std::string shooter) {
        this->createProjectile(projectileType, x, y, angle, shooter);
    };
    tank.fire(fireCallback);
}

void EntityManager::handleTankDamage(Tank& tank, double damage) {
    tank.damage(damage);
}

void EntityManager::handleTankHeal(Tank& tank, double health) {
    tank.heal(health);
}

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
        m_groundTiles.emplace_back(std::make_unique<GroundTile>(x, y, std::move(textureInfo), tileProperty.tileSpeedMultiplier));
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

    auto tank = std::unique_ptr<Tank>(new Tank(tankProperty, x, y, chassisTexture, turretTexture));

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

void EntityManager::createProjectile(const std::string& type, double x, double y, double angle, std::string shooter) {
    const auto& projectileInfo = m_projectileProperties.at(type);
    auto textureInfo = m_resourceManager.getTextureInfo(type);
    m_projectiles.emplace_back(std::make_unique<Projectile>(projectileInfo, x, y, angle, std::move(textureInfo), shooter));
}

double EntityManager::getTileSpeedMultiplier(Tank& tank) const {
    double tileSpeedMultiplier = std::numeric_limits<double>::max();
    for (const auto& groundTile : m_groundTiles) {
        if (tank.collidesWith(*groundTile)) {
            tileSpeedMultiplier = std::min(tileSpeedMultiplier, groundTile->getTileSpeedMultiplier());
        }
    }
    return tileSpeedMultiplier == std::numeric_limits<double>::max() ? 1.0 : tileSpeedMultiplier;
}

void EntityManager::handleUpdate(Tank& tank, double deltaTime, bool isPlayer) {
    double prevPositionX = tank.getX();
    double prevPositionY = tank.getY();
    double prevAngle = tank.getAngle();
    double prevTurretAngle = tank.getTurretAngle();

    tank.update(deltaTime);

    bool collided = false;
    
    if (isPlayer) {
        for (const auto& enemyTank : m_enemyTanks) {
            if (enemyTank->isAlive() && tank.collidesWith(*enemyTank)) {
                collided = true;
            }
        }
    } else {
        if (m_playerTank->isAlive() && tank.collidesWith(*m_playerTank)) {
            collided = true;
        }
    }

    for (const auto& brick : m_bricks) {
        if (tank.collidesWith(*brick) && brick->isAlive()) {
            collided = true;
        }
    }

    if (collided) {
        tank.setX(prevPositionX);
        tank.setY(prevPositionY);
        
        tank.setAngle(prevAngle);
        tank.setTurretAngle(prevTurretAngle);
    }
}

void EntityManager::handleUpdate(Projectile& projectile, double deltaTime) {
    projectile.update(deltaTime);

    if (projectile.isActive() && projectile.getShooter() != m_playerTank->getName()) {
        if (projectile.collidesWith(*m_playerTank)) {
            std::cout << projectile.getShooter() << " hit " << m_playerTank->getName() << std::endl;
            double prevHealth = m_playerTank->getHealth();
            m_playerTank->damage(projectile.getDamage());
            std::cout << m_playerTank->getName() << " health: " << prevHealth << " -> " << m_playerTank->getHealth() << std::endl;
            std::cout << m_playerTank->getName() << " status: " << (m_playerTank->isAlive() ? "alive" : "dead") << std::endl;
            projectile.setActive(false);
        }
    }

    if (projectile.isActive() && projectile.getShooter() == m_playerTank->getName()) {
        for (const auto& enemyTank : m_enemyTanks) {
            if (projectile.collidesWith(*enemyTank)) {
                std::cout << projectile.getShooter() << " hit " << enemyTank->getName() << std::endl;
                double prevHealth = enemyTank->getHealth();
                enemyTank->damage(projectile.getDamage());
                std::cout << enemyTank->getName() << " health: " << prevHealth << " -> " << enemyTank->getHealth() << std::endl;
                std::cout << enemyTank->getName() << " status: " << (enemyTank->isAlive() ? "alive" : "dead") << std::endl;
                projectile.setActive(false);
                break;
            }
        }
    }

    if (projectile.isActive()) {
        for (const auto& brick : m_bricks) {
            if (projectile.collidesWith(*brick) && brick->isAlive()) {
                std::cout << projectile.getShooter() << " hit brick" << std::endl;
                double prevHealth = brick->getHealth();
                brick->damage(projectile.getDamage());
                std::cout << "brick health: " << prevHealth << " -> " << brick->getHealth() << std::endl;
                std::cout << "brick status: " << (brick->isAlive() ? "active" : "destroyed") << std::endl;
                projectile.setActive(false);
                break;
            }
        }
    }
}