#ifndef TANK_H
#define TANK_H

#include "chassis/chassis.h"
#include "turrets/turret.h"
#include <memory>

class Tank {
public:
    Tank(double x, double y, double angle, const TextureInfo& chassisTextureInfo, const TextureInfo& turretTextureInfo, double scale = 1.0);

    void update(double deltaTime);
    void render(SDL_Renderer* renderer) const;

    void move(TankMovements::Movement movement, double deltaTime);
    void rotate(TankMovements::Rotation rotation, double deltaTime);
    void rotateTurret(TankMovements::Rotation rotation, double deltaTime);
    void fire(const Cartridge::FireCallback& fireCallback);

    double getX() const { return m_chassis->getX(); }
    double getY() const { return m_chassis->getY(); }
    double getAngle() const { return m_chassis->getAngle(); }

    void addCartridge(const std::string& cartridgeName, const std::string& projectileType, int capacity, double fireInterval, double reloadInterval);
    void cycleCartridge() { m_turret->cycleCartridge(); }
    
private:
    std::unique_ptr<Chassis> m_chassis;
    std::unique_ptr<Turret> m_turret;

    bool m_isMoving;
};

#endif // TANK_H