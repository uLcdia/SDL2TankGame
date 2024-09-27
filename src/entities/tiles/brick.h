#ifndef BRICK_H
#define BRICK_H

#include "../base/static_entity.h"

class Brick : public StaticEntity {
public:
    Brick(double x, double y, std::shared_ptr<TextureInfo> textureInfo, int health, bool vulnerable);

    int getHealth() const { return m_health; };
    bool isAlive() const { return m_health > 0; };

    void damage(double damage);
    
private:
    int m_health;
    bool m_vulnerable;
};

#endif // BRICK_H