#ifndef TANK_H
#define TANK_H

#include "chassis/chassis.h"
#include "turrets/turret.h"
#include <memory>

class Tank {
public:
    Tank(double x, double y, const TextureInfo& chassisTextureInfo, const TextureInfo& turretTextureInfo, const TextureInfo& shellTextureInfo);

    void update(double deltaTime);
    void render(SDL_Renderer* renderer) const;

    void move(TankMovements::Movement movement, double deltaTime);
    void rotate(TankMovements::Rotation rotation, double deltaTime);
    void rotateTurret(TankMovements::Rotation rotation, double deltaTime);
    void fire();

    double getX() const { return m_chassis->getX(); }
    double getY() const { return m_chassis->getY(); }
    double getAngle() const { return m_chassis->getAngle(); }

private:
    std::unique_ptr<Chassis> m_chassis;
    std::unique_ptr<Turret> m_turret;

    bool m_isMoving;
};

#endif // TANK_H