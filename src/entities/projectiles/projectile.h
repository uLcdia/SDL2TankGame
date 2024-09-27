#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "../base/dynamic_entity.h"
#include "../../properties/projectile_property.h"
#include <SDL.h>
#include <memory>
#include <string>

class Projectile : public DynamicEntity {
public:
    Projectile(const ProjectileProperty& projectileProperty, double x, double y, double angle, std::shared_ptr<TextureInfo> textureInfo, std::string shooter);
    
    virtual void update(double deltaTime) override;
    
    bool isActive() const { return m_isActive; }
    void setActive(bool isActive) { m_isActive = isActive; }

    double getDamage() const { return m_damage; }
    std::string getShooter() const { return m_shooter; }

protected:
    bool isOffScreen() const;

    bool m_isActive;
    double m_speed;
    double m_damage;
    std::string m_shooter;
};

#endif // PROJECTILE_H