#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "entity_manager.h"
#include <SDL.h>

class InputManager {
public:
    void handleInput(EntityManager& entityManager, double deltaTime);
};

#endif // INPUT_MANAGER_H