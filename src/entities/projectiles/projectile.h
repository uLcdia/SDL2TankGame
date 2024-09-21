#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "../base/dynamic_entity.h"
#include <SDL.h>

class Projectile : public DynamicEntity {
public:
    Projectile(double x, double y, double angle, const TextureInfo& textureInfo, double scale = 1.0, double speed = 300.0, double damage = 1);
    
    virtual void update(double deltaTime) override;
    virtual void render(SDL_Renderer* renderer) const override;
    
    bool isActive() const { return m_active; }

protected:
    bool m_active;
    double m_speed;
    double m_damage;
};

#endif // PROJECTILE_H