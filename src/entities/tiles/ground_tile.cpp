#include "ground_tile.h"

GroundTile::GroundTile(double x, double y, std::shared_ptr<TextureInfo> textureInfo, double tileSpeedMultiplier)
    : StaticEntity(x, y, std::move(textureInfo)), m_tileSpeedMultiplier(tileSpeedMultiplier)
{}