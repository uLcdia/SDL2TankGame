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

class EntityManager {
public:
    EntityManager(ResourceManager& resourceManager);

    void update(double deltaTime);
    void render(SDL_Renderer* renderer) const;

    Tank* getPlayerTank() { return m_playerTank.get(); }
    const std::vector<std::unique_ptr<Tank>>& getEnemyTanks() const { return m_enemyTanks; }

    void handlePlayerFire();

    bool loadLevel(const std::string& level);

private:
    bool loadMap(const std::string& mapFilePath);
    void loadMapTiles(MapParser& mapParser);
    void createTile(double x, double y, const TileProperty& tileProperty);
    bool loadTanks(const std::string& tanksFilePath);
    std::unique_ptr<Tank> createTank(const TankProperty& tankProperty);
    bool loadProjectiles(const std::string& projectilesFilePath);

    void createProjectile(const std::string& type, double x, double y, double angle);

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