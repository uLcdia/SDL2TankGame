#include "game_state_manager.h"
#include <numeric>
#include <algorithm>

void GameStateManager::update(EntityManager& entityManager, AudioManager& audioManager) {
    if (isPlayerLowHealth(entityManager)) {
        audioManager.playMusic("lowHealth");
    } else if (isEnemyLowHealth(entityManager)) {
        audioManager.playMusic("enemyLowHealth");
    } else if (isEnemyEliminated(entityManager)) {
        audioManager.playMusic("levelClear");
    } else {
        audioManager.playMusic("normal");
    }
}

bool GameStateManager::isPlayerLowHealth(const EntityManager& entityManager) {
    return entityManager.getTankHealth(entityManager.getPlayerTank()) <= LOW_HEALTH_THRESHOLD;
}

bool GameStateManager::isEnemyLowHealth(const EntityManager& entityManager) {
    for (std::size_t i = 0; i < entityManager.getEnemyTankCount(); ++i) {
        if (entityManager.getTankHealth(entityManager.getEnemyTank(i)) <= LOW_HEALTH_THRESHOLD && entityManager.getTankIsAlive(entityManager.getEnemyTank(i))) {
            return true;
        }
    }
    return false;
}

bool GameStateManager::isEnemyEliminated(const EntityManager& entityManager) {
    for (std::size_t i = 0; i < entityManager.getEnemyTankCount(); ++i) {
        if (entityManager.getTankIsAlive(entityManager.getEnemyTank(i))) {
            return false;
        }
    }
    return true;
}