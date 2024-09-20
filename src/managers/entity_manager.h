#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "../entities/tanks/tank.h"
#include "../entities/projectiles/shell.h"
#include "../entities/tiles/ground_tile.h"
#include "../entities/tiles/brick.h"
#include "resource_manager.h"
#include "../utils/map_parser.h"
#include <SDL.h>
#include <vector>
#include <memory>
#include <string>

class EntityManager {
public:
    EntityManager(ResourceManager& resourceManager);

    bool loadMap(const std::string& mapFilePath);
    void createPlayerTank(double x, double y);
    void createShell(double x, double y, double angle);

    void update(double deltaTime);
    void render(SDL_Renderer* renderer) const;

    Tank* getPlayerTank() { return m_playerTank.get(); }

private:
    void loadMapTiles(MapParser& mapParser);
    void createTile(double x, double y, const TileProperty& tileProperty);

    ResourceManager& m_resourceManager;
    std::unique_ptr<Tank> m_playerTank;
    std::vector<std::unique_ptr<Shell>> m_shells;
    std::vector<std::unique_ptr<GroundTile>> m_groundTiles;
    std::vector<std::unique_ptr<Brick>> m_bricks;
};

#endif // ENTITY_MANAGER_H