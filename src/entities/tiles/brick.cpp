#include "brick.h"

Brick::Brick(double x, double y, std::shared_ptr<TextureInfo> textureInfo, int health, bool vulnerable)
    : StaticEntity(x, y, std::move(textureInfo)), m_health(health), m_vulnerable(vulnerable)
{}

void Brick::damage(double damage) {
    if (m_vulnerable && isAlive()) {
        m_health -= damage;
    }
}