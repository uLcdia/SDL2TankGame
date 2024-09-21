#ifndef TURRET_H
#define TURRET_H

#include "../tank_movements.h"
#include "../../base/dynamic_entity.h"
#include "../cartridge/cartridge.h"
#include <SDL.h>
#include <vector>

class Turret : public DynamicEntity {
public:
    Turret(double x, double y, double angle, const TextureInfo& turretTextureInfo, double scale = 1.0);
    
    void update(double deltaTime) override;
    void render(SDL_Renderer* renderer) const override;

    void rotate(TankMovements::Rotation rotation, double deltaTime, bool isMoving);

    void fire(const Cartridge::FireCallback& fireCallback);

    void addCartridge(const std::string& name, const std::string& projectileType, int capacity, double fireInterval, double reloadInterval);
    void cycleCartridge();
    const Cartridge* getCurrentCartridge() const;

private:
    std::vector<Cartridge> m_cartridges;
    std::size_t m_currentCartridgeIndex;

    static constexpr double ROTATE_SPEED = 90.0;  // degrees per second
    static constexpr double PROJECTILE_SPAWN_DISTANCE = 65.0; // distance from the turret's pivot point to the spawn point of the projectile
};

#endif // TURRET_H