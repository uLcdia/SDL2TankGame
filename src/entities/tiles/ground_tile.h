#ifndef GROUND_TILE_H
#define GROUND_TILE_H

#include "../base/static_entity.h"

class GroundTile : public StaticEntity {
public:
    GroundTile(double x, double y, const TextureInfo& textureInfo);
};

#endif // GROUND_TILE_H