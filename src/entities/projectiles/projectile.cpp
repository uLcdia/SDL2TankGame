#include "projectile.h"
#include <cmath>

Projectile::Projectile(double x, double y, double angle, const TextureInfo& textureInfo, double scale, double speed, double damage)
    : DynamicEntity(x, y, angle, textureInfo, scale), m_active(true), m_speed(speed), m_damage(damage)
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
