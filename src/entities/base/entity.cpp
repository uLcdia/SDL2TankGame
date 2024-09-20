#include "entity.h"
#include <SDL.h>

Entity::Entity(double x, double y, const TextureInfo& textureInfo)
    : m_x(x), m_y(y), m_textureInfo(&textureInfo) {}

void Entity::render(SDL_Renderer* renderer) const {
    SDL_Rect destRect = getRect();
    SDL_RenderCopy(renderer, m_textureInfo->texture, nullptr, &destRect);
}

bool Entity::collidesWith(const Entity& other) const {
    SDL_Rect rect1 = getRect();
    SDL_Rect rect2 = other.getRect();
    return SDL_HasIntersection(&rect1, &rect2) == SDL_TRUE;
}

SDL_Rect Entity::getRect() const {
    return {
        static_cast<int>(m_x),
        static_cast<int>(m_y),
        m_textureInfo->width,
        m_textureInfo->height
    };
}