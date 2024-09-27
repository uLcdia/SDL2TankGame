#include "projectile.h"
#include <cmath>

Projectile::Projectile(const ProjectileProperty& projectileProperty, double x, double y, double angle, std::shared_ptr<TextureInfo> textureInfo, std::string shooter)
    : DynamicEntity(x, y, angle, std::move(textureInfo), projectileProperty.scale),
      m_active(true), m_speed(projectileProperty.speed), m_damage(projectileProperty.damage), m_shooter(shooter)
{
    // Projectile is fired when created
    double vx = std::sin(m_angle * M_PI / 180.0) * m_speed;
    double vy = -std::cos(m_angle * M_PI / 180.0) * m_speed;
    setVelocity(vx, vy);
}

void Projectile::update(double deltaTime) {
    if (!m_active) return;
    DynamicEntity::update(deltaTime);
}

void Projectile::render(SDL_Renderer* renderer) const {
    if (!m_active) return;
    DynamicEntity::render(renderer);
}
