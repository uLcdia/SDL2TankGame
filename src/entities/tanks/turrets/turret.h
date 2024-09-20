#ifndef TURRET_H
#define TURRET_H

#include "../tank_movements.h"
#include "../../base/dynamic_entity.h"
#include "../../projectiles/shell.h"
#include <SDL.h>
#include <vector>

class Turret : public DynamicEntity {
public:
    Turret(double x, double y, double angle, const TextureInfo& turretTextureInfo, const TextureInfo& shellTextureInfo, double scale = 1.0);
    
    void update(double deltaTime) override;
    void render(SDL_Renderer* renderer) const override;

    void rotate(TankMovements::Rotation rotation, double deltaTime, bool isMoving);

    void fire();
    void updateShells(double deltaTime);
    void renderShells(SDL_Renderer* renderer) const;

private:
    const TextureInfo* m_turretTextureInfo;
    const TextureInfo* m_shellTextureInfo;

    std::vector<Shell> m_shells;

    double m_fireTimer;

    static constexpr double ROTATE_SPEED = 90.0;  // degrees per second
    static constexpr double FIRE_COOLDOWN = 0.5;  // seconds
};

#endif // TURRET_H