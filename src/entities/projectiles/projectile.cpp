#include "projectile.h"
#include <cmath>

Projectile::Projectile(const ProjectileProperty& projectileProperty, double x, double y, double angle, std::shared_ptr<TextureInfo> textureInfo, std::string shooter)
    : DynamicEntity(x, y, angle, std::move(textureInfo), projectileProperty.scale),
      m_isActive(true), m_speed(projectileProperty.speed), m_damage(projectileProperty.damage), m_shooter(shooter)
{
    // Projectile is fired when created
    double vx = std::sin(m_angle * M_PI / 180.0) * m_speed;
    double vy = -std::cos(m_angle * M_PI / 180.0) * m_speed;
    setVelocity(vx, vy);
}

void Projectile::update(double deltaTime) {
    if (!isActive()) return;
    if (isOffScreen()) {
        setActive(false);
    }
    DynamicEntity::update(deltaTime);
}

bool Projectile::isOffScreen() const {
    // No one is playing on a 4000x3200 map (right?)
    return getX() < 0 || getX() > 4000 || getY() < 0 || getY() > 3200;
}