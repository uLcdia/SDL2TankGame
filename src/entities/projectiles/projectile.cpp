#include "projectile.h"
#include <cmath>

Projectile::Projectile(const ProjectileProperty& projectileProperty, double x, double y, double angle, std::shared_ptr<TextureInfo> textureInfo)
    : DynamicEntity(x, y, angle, std::move(textureInfo), projectileProperty.scale),
      m_active(true), m_speed(projectileProperty.speed), m_damage(projectileProperty.damage)
{
    // Projectile is fired when created
    double vx = std::sin(m_angle * M_PI / 180.0) * m_speed;
    double vy = -std::cos(m_angle * M_PI / 180.0) * m_speed;
    setVelocity(vx, vy);
}

void Projectile::update(double deltaTime) {
    if (!m_active) return;

    DynamicEntity::update(deltaTime);

    // TODO: Use collision system to check if projectile is out of screen bounds
    if (getX() < 0 || getX() > 1600 || getY() < 0 || getY() > 960) {
        m_active = false;
    }
}

void Projectile::render(SDL_Renderer* renderer) const {
    if (!m_active) return;
    DynamicEntity::render(renderer);
}
