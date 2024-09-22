#include "brick.h"

Brick::Brick(double x, double y, std::shared_ptr<TextureInfo> textureInfo, int health, bool vulnerable)
    : StaticEntity(x, y, std::move(textureInfo)), m_health(health), m_vulnerable(vulnerable)
{}

bool Brick::hit() {
    if (m_vulnerable) {
        m_health--;
        return m_health <= 0;
    }
    return false;
}

bool Brick::isDestroyed() const {
    return m_health <= 0;
}