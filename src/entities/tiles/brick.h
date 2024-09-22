#ifndef BRICK_H
#define BRICK_H

#include "../base/static_entity.h"

class Brick : public StaticEntity {
public:
    Brick(double x, double y, std::shared_ptr<TextureInfo> textureInfo, int health, bool vulnerable);
    bool hit();
    bool isDestroyed() const;

private:
    int m_health;
    bool m_vulnerable;
};

#endif // BRICK_H