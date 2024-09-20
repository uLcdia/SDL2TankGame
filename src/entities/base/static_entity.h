#ifndef STATIC_ENTITY_H
#define STATIC_ENTITY_H

#include "entity.h"

class StaticEntity : public Entity {
public:
    StaticEntity(double x, double y, const TextureInfo& textureInfo);
    virtual ~StaticEntity() = default;

    virtual void update(double deltaTime) override;
    virtual void render(SDL_Renderer* renderer) const override;
};

#endif // STATIC_ENTITY_H