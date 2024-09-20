#ifndef CHASSIS_H
#define CHASSIS_H

#include "../tank_movements.h"
#include "../../base/dynamic_entity.h"
#include <SDL.h>
#include <vector>

class Chassis : public DynamicEntity {
public:
    Chassis(double x, double y, double angle, const TextureInfo& chassisTextureInfo, double scale = 1.0);

    void move(TankMovements::Movement movement, double deltaTime);
    void rotate(TankMovements::Rotation rotation, double deltaTime, bool isMoving);

private:
    const TextureInfo* m_chassisTextureInfo;

    static constexpr double MOVE_SPEED = 100.0;   // pixels per second
    static constexpr double ROTATE_SPEED = 90.0;  // degrees per second
};

#endif // CHASSIS_H