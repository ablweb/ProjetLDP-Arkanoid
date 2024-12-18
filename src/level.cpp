#include "level.hpp"

#include <memory>

#include "entity.hpp"
#include "utils.hpp"

LevelManager::LevelManager()
  : testRect(std::make_shared<TestRectangle>(tpl{100, 100}, 100, 100, COLORS::RED)) {
}

LevelManager::~LevelManager() {}

void LevelManager::movePaletteRigth() {
  testRect->move(10, 0);
}
void LevelManager::movePaletteLeft() {
  testRect->move(-10, 0);
}
void LevelManager::update() {
  /// Here add state update of the game like ball moving
}

std::shared_ptr<TestRectangle> LevelManager::getTestRect() const {
  return testRect;
}
