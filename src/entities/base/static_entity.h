#ifndef STATIC_ENTITY_H
#define STATIC_ENTITY_H

#include "entity.h"

class StaticEntity : public Entity {
public:
    StaticEntity(double x, double y, std::shared_ptr<TextureInfo> textureInfo);

    void update([[maybe_unused]] double deltaTime) override;
    void render(SDL_Renderer* renderer) const override;
};

#endif // STATIC_ENTITY_H