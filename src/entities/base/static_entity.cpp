#include "static_entity.h"

StaticEntity::StaticEntity(double x, double y, const TextureInfo& textureInfo)
    : Entity(x, y, textureInfo)
{}

void StaticEntity::update(double deltaTime)
{}

void StaticEntity::render(SDL_Renderer* renderer) const {
    SDL_Rect destRect = getRect();

    SDL_RenderCopyEx(
        renderer,
        m_textureInfo->texture,
        nullptr,
        &destRect,
        0,
        nullptr,
        SDL_FLIP_NONE
    );
}