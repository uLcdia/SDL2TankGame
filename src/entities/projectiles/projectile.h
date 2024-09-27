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
    virtual void render(SDL_Renderer* renderer) const override;
    
    bool isActive() const { return m_active; }
    void setActive(bool active) { m_active = active; }

    double getDamage() const { return m_damage; }
    std::string getShooter() const { return m_shooter; }

protected:
    bool m_active;
    double m_speed;
    double m_damage;
    std::string m_shooter;
};

#endif // PROJECTILE_H