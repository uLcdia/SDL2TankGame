#ifndef CHASSIS_H
#define CHASSIS_H

#include "../tank_movements.h"
#include "../../base/dynamic_entity.h"
#include <SDL.h>
#include <vector>

class Chassis : public DynamicEntity {
public:
    Chassis(double x, double y, const TextureInfo& chassisTextureInfo);
    
    void update(double deltaTime) override;
    void render(SDL_Renderer* renderer) const override;

    void move(TankMovements::Movement movement, double deltaTime);
    void rotate(TankMovements::Rotation rotation, double deltaTime, bool isMoving);

    double getAngle() const { return m_angle; }
    void setAngle(double angle) { m_angle = angle; }

    SDL_Rect getRect() const override;

private:
    double m_angle;

    const TextureInfo* m_chassisTextureInfo;

    static constexpr double MOVE_SPEED = 100.0;   // pixels per second
    static constexpr double ROTATE_SPEED = 90.0;  // degrees per second
};

#endif // CHASSIS_H