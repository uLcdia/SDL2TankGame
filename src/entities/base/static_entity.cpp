#include "static_entity.h"

StaticEntity::StaticEntity(double x, double y, std::shared_ptr<TextureInfo> textureInfo)
    : Entity(x, y, std::move(textureInfo))
{}

void StaticEntity::update([[maybe_unused]] double deltaTime)
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