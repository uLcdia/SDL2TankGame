#ifndef TANK_MOVEMENTS_H
#define TANK_MOVEMENTS_H

namespace TankMovements {
    enum class Movement {
        FORWARD,
        BACKWARD,
        NONE,
    };

    enum class Rotation {
        CLOCKWISE,
        COUNTERCLOCKWISE,
    };

    static constexpr double ROTATE_SPEED_MULTIPLIER = 0.5;
}

#endif // TANK_MOVEMENTS_H