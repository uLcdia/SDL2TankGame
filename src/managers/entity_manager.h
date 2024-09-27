#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "../entities/tanks/tank.h"
#include "../entities/projectiles/projectile.h"
#include "../entities/tiles/ground_tile.h"
#include "../entities/tiles/brick.h"
#include "resource_manager.h"
#include "../utils/map_parser.h"
#include "../utils/tank_parser.h"
#include "../utils/projectile_parser.h"
#include <SDL.h>
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>

/**
 * @class EntityManager
 * @brief Manages all game entities, including tanks, projectiles, and map tiles.
 *
 * This class is responsible for creating, updating, and rendering all game entities.
 * It also handles level loading, including map tiles, tanks, and projectiles.
 */
class EntityManager {
public:
    EntityManager(ResourceManager& resourceManager);

    void update(double deltaTime);
    void render(SDL_Renderer* renderer) const;

    Tank& getPlayerTank() { return *m_playerTank; }
    const Tank& getPlayerTank() const { return *m_playerTank; }
    Tank& getEnemyTank(std::size_t index) { return *m_enemyTanks[index]; }
    const Tank& getEnemyTank(std::size_t index) const { return *m_enemyTanks[index]; }

    std::string getTankName(const Tank& tank) const;
    double getTankHealth(const Tank& tank) const;
    bool getTankIsAlive(const Tank& tank) const;
    
    void handleTankMovement(Tank& tank, TankMovements::Movement movement);
    void handleTankRotation(Tank& tank, TankMovements::Rotation rotation);
    void handleTankTurretRotation(Tank& tank, TankMovements::Rotation rotation);
    void handleTankCycleCartridge(Tank& tank);
    void handleTankFire(Tank& tank);
    void handleTankDamage(Tank& tank, double damage);
    void handleTankHeal(Tank& tank, double health);

    /**
     * @brief Loads a game level, including map, tanks, and projectiles.
     * @param level The name or path of the level to load.
     * @return True if the level was successfully loaded, false otherwise.
     */
    bool loadLevel(const std::string& level);

private:
    bool loadMap(const std::string& mapFilePath);
    void loadMapTiles(MapParser& mapParser);
    void createTile(double x, double y, const TileProperty& tileProperty);
    bool loadTanks(const std::string& tanksFilePath);
    std::unique_ptr<Tank> createTank(const TankProperty& tankProperty);
    bool loadProjectiles(const std::string& projectilesFilePath);

    void createProjectile(const std::string& type, double x, double y, double angle, std::string shooter);

    double getTileSpeedMultiplier(Tank& tank) const;

    void handleUpdate(Tank& tank, double deltaTime, bool isPlayer);
    void handleUpdate(Projectile& projectile, double deltaTime);

    ResourceManager& m_resourceManager;

    double m_tileSize;

    std::unordered_map<std::string, ProjectileProperty> m_projectileProperties;
    
    std::unique_ptr<Tank> m_playerTank;
    std::vector<std::unique_ptr<Tank>> m_enemyTanks;
    std::vector<std::unique_ptr<Projectile>> m_projectiles;
    std::vector<std::unique_ptr<GroundTile>> m_groundTiles;
    std::vector<std::unique_ptr<Brick>> m_bricks;
};

#endif // ENTITY_MANAGER_H