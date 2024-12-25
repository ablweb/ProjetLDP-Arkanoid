#include "stateManager.hpp"

#include <memory>

#include "entity.hpp"
#include "utils.hpp"

StateManager::StateManager()
  : testRect(std::make_shared<TestRectangle>(tpl{100, 100}, 100, 100, COLORS::RED)) {
}

StateManager::~StateManager() {}

void StateManager::movePaletteRigth() {
  testRect->move(10, 0);
  notifyListener(testRect.get());
}
void StateManager::movePaletteLeft() {
  testRect->move(-10, 0);
  notifyListener(testRect.get());
}
void StateManager::update() {
  // Here add state update of the game like ball moving
  // notifyObserver(...);
}

std::shared_ptr<TestRectangle> StateManager::getTestRect() const {
  return testRect;
}
