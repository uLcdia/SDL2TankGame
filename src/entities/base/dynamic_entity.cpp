#include "dynamic_entity.h"

DynamicEntity::DynamicEntity(double x, double y, double angle, const TextureInfo& textureInfo, double scale)
    : Entity(x, y, textureInfo),
      m_vx(0), m_vy(0), 
      m_angle(angle),
      m_scale(scale) 
{}

void DynamicEntity::update(double deltaTime) {
    // Update position based on velocity
    m_x += m_vx * deltaTime;
    m_y += m_vy * deltaTime;
}

void DynamicEntity::render(SDL_Renderer* renderer) const {
    SDL_Rect destRect = getRect();
    SDL_RenderCopyEx(renderer, m_textureInfo->texture, nullptr, &destRect, m_angle, nullptr, SDL_FLIP_NONE);
}

void DynamicEntity::setVelocity(double vx, double vy) {
    m_vx = vx;
    m_vy = vy;
}

SDL_Rect DynamicEntity::getRect() const {
    return {
        static_cast<int>(m_x - getScaledWidth() / 2),
        static_cast<int>(m_y - getScaledHeight() / 2),
        getScaledWidth(),
        getScaledHeight()
    };
}