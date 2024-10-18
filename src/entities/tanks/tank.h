#ifndef TANK_H
#define TANK_H

#include "../../properties/tank_property.h"
#include "chassis/chassis.h"
#include "turrets/turret.h"
#include <memory>
#include <string>

class Tank {
private:
    friend class EntityManager;
    
    Tank(const TankProperty& tankProperty, double x, double y, std::shared_ptr<TextureInfo> chassisTexture, std::shared_ptr<TextureInfo> turretTexture);

    void update(double deltaTime);
    void render(SDL_Renderer* renderer) const;

    void move(TankMovements::Movement movement, double tileSpeedMultiplier);
    void rotate(TankMovements::Rotation rotation, double rotationSpeed);
    void rotateTurret(TankMovements::Rotation rotation);
    void cycleCartridge() { m_turret->cycleCartridge(); }
    void fire(const Cartridge::FireCallback& fireCallback) { m_turret->fire(fireCallback, m_name); }
    void damage(double damage);
    void heal(double health);

    std::string getName() const { return m_name; }
    double getHealth() const { return m_health; }
    double getMaxHealth() const { return m_maxHealth; }
    bool isAlive() const { return m_health > 0; }

    double getX() const { return m_chassis->getX(); }
    double getY() const { return m_chassis->getY(); }
    double getAngle() const { return m_chassis->getAngle(); }
    double getTurretAngle() const { return m_turret->getAngle(); }
    void setX(double x) { m_chassis->setX(x); m_turret->setX(x); }
    void setY(double y) { m_chassis->setY(y); m_turret->setY(y); }
    void setAngle(double angle) { m_chassis->setAngle(angle); }
    void setTurretAngle(double angle) { m_turret->setAngle(angle); }
    
    bool collidesWith(const Entity& other) const;
    bool collidesWith(const DynamicEntity& other) const;
    bool collidesWith(const Tank& other) const;

    void addCartridge(const Cartridge& cartridge) { m_turret->addCartridge(cartridge); }

    operator DynamicEntity&() { return *m_chassis; } // For Projectile::collidesWith(const DynamicEntity& other)

    std::string m_name;  
    double m_health;
    double m_maxHealth;
    bool m_isMoving;
    std::unique_ptr<Chassis> m_chassis;
    std::unique_ptr<Turret> m_turret;
    double m_chassisRotationSpeed;
    double m_turretRotationSpeed;
};

#endif // TANK_H