#ifndef STATIC_ENTITY_H
#define STATIC_ENTITY_H

#include "entity.h"

/**
 * @class StaticEntity
 * @brief Represents an entity that does not move or change over time.
 * Identical to Entity, keeping it for now in case of future changes.
 */
class StaticEntity : public Entity {
public:
    StaticEntity(double x, double y, std::shared_ptr<TextureInfo> textureInfo);
};

#endif // STATIC_ENTITY_H