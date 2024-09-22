#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "../base/dynamic_entity.h"
#include "../../properties/projectile_property.h"
#include <SDL.h>
#include <memory>

class Projectile : public DynamicEntity {
public:
    Projectile(const ProjectileProperty& projectileProperty, double x, double y, double angle, std::shared_ptr<TextureInfo> textureInfo);
    
    virtual void update(double deltaTime) override;
    virtual void render(SDL_Renderer* renderer) const override;
    
    bool isActive() const { return m_active; }

protected:
    bool m_active;
    double m_speed;
    double m_damage;
};

#endif // PROJECTILE_H