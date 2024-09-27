#include "entity.h"
#include <SDL.h>

Entity::Entity(double x, double y, std::shared_ptr<TextureInfo> textureInfo)
    : m_x(x), m_y(y), m_textureInfo(std::move(textureInfo)) {}

void Entity::render(SDL_Renderer* renderer) const {
    SDL_Rect destRect = getRect();
    SDL_RenderCopy(renderer, m_textureInfo->texture, nullptr, &destRect);
}

void Entity::renderEdges(SDL_Renderer* renderer) const {
    auto vertices = getVertices();

    for (std::size_t i = 0; i < vertices.size(); ++i) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(renderer, vertices[i].x, vertices[i].y, vertices[(i + 1) % vertices.size()].x, vertices[(i + 1) % vertices.size()].y);
    }
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