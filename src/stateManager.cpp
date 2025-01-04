#include "stateManager.hpp"

#include "entity.hpp"
#include "level.hpp"

StateManager::StateManager(LevelSPtr level) : lvl(level) {}

StateManager::~StateManager() {}

void StateManager::movePaddleRight() {
  lvl->paddle->move(1); 
  if (lvl->ball->isAttached) {
    lvl->ball->setPos(lvl->paddle->x()); // Sync Ball position with paddle
  }
}
void StateManager::movePaddleLeft() { 
  lvl->paddle->move(0); 
  if (lvl->ball->isAttached) {
    lvl->ball->setPos(lvl->paddle->x()); // Sync Ball position with paddle
  }
}
void StateManager::launchBall() {
  if (lvl->ball->isAttached) {
    lvl->ball->go();
  }
}
void StateManager::update() {
  // Here add state update that should happen each frame
  checkAllCollision();
  lvl->ball->move();
}
void StateManager::checkAllCollision() {
  for (auto& mask : lvl->getColisionMasks()) {
    for (const auto entityG : mask.group) {
      const auto ball = dynamic_cast<Ball*>(entityG);
      for (const auto entityM : mask.masked) {
        if (const auto other = dynamic_cast<Paddle*>(entityM)) {
          if(ball->checkCollision(other)) {
            ball->collisionDetected(other,ball->colPoint);
            other->collisionDetected(ball,ball->colPoint);
          }
        }
        if (const auto other = dynamic_cast<Brick*>(entityM)) {
          if(ball->checkCollision(other)) {
            ball->collisionDetected(other,ball->colPoint);
            other->collisionDetected(ball,ball->colPoint);
          }
        }
      }
    }
  }
}
