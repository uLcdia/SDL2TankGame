#include "ground_tile.h"

GroundTile::GroundTile(double x, double y, std::shared_ptr<TextureInfo> textureInfo)
    : StaticEntity(x, y, std::move(textureInfo))
{}