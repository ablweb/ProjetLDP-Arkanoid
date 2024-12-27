#include "stateManager.hpp"

#include <memory>

#include "entity.hpp"
#include "level.hpp"

StateManager::StateManager(LevelSPtr level) : lvl(level) {}

StateManager::~StateManager() {}

void StateManager::movePaddleRight() { lvl->testRect->move(10, 0); }
void StateManager::movePaddleLeft() { lvl->testRect->move(-10, 0); }
void StateManager::update() {
  // Here add state update of the game like ball moving
}
