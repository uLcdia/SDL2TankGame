#include "dynamic_entity.h"

DynamicEntity::DynamicEntity(double x, double y, const TextureInfo& textureInfo)
    : Entity(x, y, textureInfo), m_vx(0), m_vy(0) {}

void DynamicEntity::update(double deltaTime) {
    // Update position based on velocity
    m_x += m_vx * deltaTime;
    m_y += m_vy * deltaTime;
}

void DynamicEntity::setVelocity(double vx, double vy) {
    m_vx = vx;
    m_vy = vy;
}