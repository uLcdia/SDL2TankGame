#include "static_entity.h"

StaticEntity::StaticEntity(double x, double y, std::shared_ptr<TextureInfo> textureInfo)
    : Entity(x, y, std::move(textureInfo))
{}