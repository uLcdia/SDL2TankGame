#include "input_manager.h"

void InputManager::handleInput(EntityManager& entityManager) {
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    auto& playerTank = entityManager.getPlayerTank();

    if (keystate[SDL_SCANCODE_W]) {
        entityManager.handleTankMovement(playerTank, TankMovements::Movement::FORWARD);
    } else if (keystate[SDL_SCANCODE_S]) {
        entityManager.handleTankMovement(playerTank, TankMovements::Movement::BACKWARD);
    } else {
        entityManager.handleTankMovement(playerTank, TankMovements::Movement::NONE);
    }

    if (keystate[SDL_SCANCODE_A]) {
        entityManager.handleTankRotation(playerTank, TankMovements::Rotation::COUNTERCLOCKWISE);
    } else if (keystate[SDL_SCANCODE_D]) {
        entityManager.handleTankRotation(playerTank, TankMovements::Rotation::CLOCKWISE);
    } else {
        entityManager.handleTankRotation(playerTank, TankMovements::Rotation::NONE);
    }

    if (keystate[SDL_SCANCODE_Q]) {
        entityManager.handleTankTurretRotation(playerTank, TankMovements::Rotation::COUNTERCLOCKWISE);
    } else if (keystate[SDL_SCANCODE_E]) {
        entityManager.handleTankTurretRotation(playerTank, TankMovements::Rotation::CLOCKWISE);
    }

    if (keystate[SDL_SCANCODE_SPACE]) {
        entityManager.handleTankFire(playerTank);
    }
}

void InputManager::handleEvent(SDL_Event& event, EntityManager& entityManager) {
    auto& playerTank = entityManager.getPlayerTank();

    switch (event.type) {
        case SDL_KEYDOWN:
            if (event.key.keysym.scancode == SDL_SCANCODE_R && !m_rKeyPressed) {
                m_rKeyPressed = true;
                entityManager.handleTankCycleCartridge(playerTank);
            }
            break;
        case SDL_KEYUP:
            if (event.key.keysym.scancode == SDL_SCANCODE_R) {
                m_rKeyPressed = false;
            }
            break;
    }
}