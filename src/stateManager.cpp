#include "stateManager.hpp"

#include <memory>

#include "entity.hpp"
#include "level.hpp"

StateManager::StateManager(LevelSPtr level)
  : lvl(level) {}

StateManager::~StateManager() {}

void StateManager::movePaletteRigth() {
  lvl->testRect->move(10, 0);
}
void StateManager::movePaletteLeft() {
  lvl->testRect->move(-10, 0);
}
void StateManager::update() {
  // Here add state update of the game like ball moving
}
