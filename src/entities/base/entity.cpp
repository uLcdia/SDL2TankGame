#include "entity.h"
#include <SDL.h>

Entity::Entity(double x, double y, std::shared_ptr<TextureInfo> textureInfo)
    : m_x(x), m_y(y), m_textureInfo(std::move(textureInfo)) {}

void Entity::render(SDL_Renderer* renderer) const {
    SDL_Rect destRect = getRect();
    SDL_RenderCopy(renderer, m_textureInfo->texture, nullptr, &destRect);
}

SDL_Rect Entity::getRect() const {
    return {
        static_cast<int>(m_x),
        static_cast<int>(m_y),
        m_textureInfo->width,
        m_textureInfo->height
    };
}

std::array<SDL_Point, 4> Entity::getVertices() const {
    std::array<SDL_Point, 4> vertices;
    SDL_Rect rect = getRect();
    vertices[0] = {rect.x, rect.y};
    vertices[1] = {rect.x + rect.w, rect.y};
    vertices[2] = {rect.x + rect.w, rect.y + rect.h};
    vertices[3] = {rect.x, rect.y + rect.h};
    return vertices;
}