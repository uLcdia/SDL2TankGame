#include "input_manager.h"

void InputManager::handleInput(EntityManager& entityManager, double deltaTime) {
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    Tank* playerTank = entityManager.getPlayerTank();
    
    if (!playerTank) return;

    if (keystate[SDL_SCANCODE_W]) {
        playerTank->move(TankMovements::Movement::FORWARD, deltaTime);
    } else if (keystate[SDL_SCANCODE_S]) {
        playerTank->move(TankMovements::Movement::BACKWARD, deltaTime);
    } else {
        playerTank->move(TankMovements::Movement::NONE, deltaTime);
    }

    if (keystate[SDL_SCANCODE_A]) {
        playerTank->rotateTank(TankMovements::Rotation::COUNTERCLOCKWISE, deltaTime);
    } else if (keystate[SDL_SCANCODE_D]) {
        playerTank->rotateTank(TankMovements::Rotation::CLOCKWISE, deltaTime);
    }

    if (keystate[SDL_SCANCODE_Q]) {
        playerTank->rotateTurret(TankMovements::Rotation::COUNTERCLOCKWISE, deltaTime);
    } else if (keystate[SDL_SCANCODE_E]) {
        playerTank->rotateTurret(TankMovements::Rotation::CLOCKWISE, deltaTime);
    }

    if (keystate[SDL_SCANCODE_SPACE]) {
        playerTank->fire();
    }
}