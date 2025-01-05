#include "stateManager.hpp"

#include "entity.hpp"
#include "level.hpp"
#include "config.hpp"  


StateManager::StateManager(LevelSPtr level) 
  : lvl(std::move(level)), lives(3) {}

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
if (lvl->ball->y() > DISPLAY_HEIGHT) {  // Example condition: ball goes out of bounds
        loseLife();
        if (lives > 0) {
            // Reset ball position or launch new ball
        }
    }
  // Here add state update that should happen each frame

  checkAllCollision();
  lvl->ball->move();

}

bool StateManager::isVictory() const {
  return lvl->bricks->getContainer().empty(); // Suppose que `getContainer` retourne les briques restantes.
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

void StateManager::loseLife() {
  lives--;
  if (lives <= 0) {
    // Display game over message
    env.DISPLAY = al_create_display(800, 600);
    al_draw_textf(env.FONT, al_map_rgb(255, 0, 0), 400, 300, ALLEGRO_ALIGN_CENTRE, "Game Over! Score: %d", lvl->score);
    al_flip_display();
    al_rest(3);  // Wait for 3 seconds to show the game over screen
    exit(0);  // Close the game
  }
}
