#ifndef TANK_H
#define TANK_H

#include "../../properties/tank_property.h"
#include "chassis/chassis.h"
#include "turrets/turret.h"
#include <memory>
#include <string>

class Tank {
public:
    Tank(const TankProperty& tankProperty, double x, double y, std::shared_ptr<TextureInfo> chassisTexture, std::shared_ptr<TextureInfo> turretTexture);

    void update(double deltaTime);
    void render(SDL_Renderer* renderer) const;

    void move(TankMovements::Movement movement);
    void rotate(TankMovements::Rotation rotation, double deltaTime);
    void rotateTurret(TankMovements::Rotation rotation, double deltaTime);
    void fire(const Cartridge::FireCallback& fireCallback) { m_turret->fire(fireCallback); }

    double getX() const { return m_chassis->getX(); }
    double getY() const { return m_chassis->getY(); }
    double getAngle() const { return m_chassis->getAngle(); }

    void addCartridge(const Cartridge& cartridge) { m_turret->addCartridge(cartridge); }
    void cycleCartridge() { m_turret->cycleCartridge(); }
    
private:
    std::string m_name;

    std::unique_ptr<Chassis> m_chassis;
    std::unique_ptr<Turret> m_turret;

    double m_chassisRotationSpeed;
    double m_turretRotationSpeed;
    
    double m_health;

    bool m_isMoving;
};

#endif // TANK_H