#include "controller.hpp"

#include <allegro5/keycodes.h>
#include <allegro5/mouse.h>

#include <cstddef>
#include <exception>
#include <iostream>
#include <memory>
#include <sys/types.h>
#include <utility>

#include "env.hpp"
#include "level.hpp"
#include "renderer.hpp"
#include "stateManager.hpp"

Controller::Controller(StateManagerUPtr stateManager, RendererUPtr renderer,
                       LevelSPtr level)
    : sm(std::move(stateManager)), rndr(std::move(renderer)), lvl(level),
      loader(std::make_unique<LevelLoader>()),
      keyState(false), currentLevel(-1) {}

Controller::~Controller() {}

int Controller::handleInput() {
  int ret = 0;
  if (env.EVENT.type == ALLEGRO_EVENT_KEY_DOWN) {
    if (GAME_STATE==VICTORY)GAME_STATE=IN_GAME;
    if (GAME_STATE==LOSE)GAME_STATE=IN_GAME;
    switch (env.EVENT.keyboard.keycode) {
      case ALLEGRO_KEY_A:
        if (LOG_LEVEL>=3)std::cerr<<"|Controller::handleInput() -> KEY_A_DOWN:LEFT\n";
        keyState[LEFT] = true; break;
      case ALLEGRO_KEY_Q:
        if (LOG_LEVEL>=3)std::cerr<<"|Controller::handleInput() -> KEY_Q_DOWN:LEFT\n";
        keyState[LEFT] = true; break;
      case ALLEGRO_KEY_D:
        if (LOG_LEVEL>=3)std::cerr<<"|Controller::handleInput() -> KEY_D_DOWN:RIGHT\n";
        keyState[RIGHT] = true; break;
      case ALLEGRO_KEY_P:
        if (LOG_LEVEL>=3)std::cerr<<"|Controller::handleInput() -> KEY_P_DOWN:RIGHT\n";
        keyState[RIGHT] = true; break;
      case ALLEGRO_KEY_SPACE:
        if (LOG_LEVEL>=3)std::cerr<<"|Controller::handleInput() -> KEY_SPACE_DOWN:ACTION\n";
        sm->launchBall(); break;
      case ALLEGRO_KEY_RIGHT:
        if (LOG_LEVEL>=3)std::cerr<<"|Controller::handleInput() -> KEY_RIGHT_DOWN:NEXT\n";
        loadLevel(1, true); break;
      case ALLEGRO_KEY_LEFT:
        if (LOG_LEVEL>=3)std::cerr<<"|Controller::handleInput() -> KEY_LEFT_DOWN:PREVIOUS\n";
        loadLevel(0, true); break;
      case ALLEGRO_KEY_R:
        if (LOG_LEVEL>=3)std::cerr<<"|Controller::handleInput() -> KEY_R_DOWN:RELOAD\n";
        reloadLevels(); break;
      case ALLEGRO_KEY_ESCAPE:
        if (LOG_LEVEL>=3)std::cerr<<"|Controller::handleInput() -> KEY_ESCAPE_DOWN:QUIT\n";
        ret = -1; break;
      default: break;
    }
  }
  if (env.EVENT.type == ALLEGRO_EVENT_KEY_UP) {
    switch (env.EVENT.keyboard.keycode) {
      case ALLEGRO_KEY_A:
        if (LOG_LEVEL>=3)std::cerr<<"|Controller::handleInput() -> KEY_A_UP:LEFT\n";
        keyState[LEFT] = false; break;
      case ALLEGRO_KEY_Q:
        if (LOG_LEVEL>=3)std::cerr<<"|Controller::handleInput() -> KEY_Q_UP:LEFT\n";
        keyState[LEFT] = false; break;
      case ALLEGRO_KEY_D:
        if (LOG_LEVEL>=3)std::cerr<<"|Controller::handleInput() -> KEY_D_UP:RIGHT\n";
        keyState[RIGHT] = false; break;
      case ALLEGRO_KEY_P:
        if (LOG_LEVEL>=3)std::cerr<<"|Controller::handleInput() -> KEY_P_UP:RIGHT\n";
        keyState[RIGHT] = false; break;
      default: break;
    }
  }
  if(MOUSE) handleMouse();
  handleContiniousKeyPress();
  return ret;
}
void Controller::handleMouse() {
  int deadZonr = 12;
  if (env.MOUSE_STATE.x>(int)lvl->paddle->x() + deadZonr) {
    sm->movePaddleRight();
  } else if (env.MOUSE_STATE.x<(int)lvl->paddle->x() - deadZonr) {
    sm->movePaddleLeft();
  }
}

void Controller::handleContiniousKeyPress() {
  if (keyState[LEFT]) {
    sm->movePaddleLeft();
  } else if (keyState[RIGHT]) {
    sm->movePaddleRight();
  }
}

void Controller::updateGameState() {
  sm->update(); 
}
void Controller::checkGameState() {
  if (sm->isVictory()) {
    // set global state to VICTORY
    GAME_STATE = VICTORY;
    loadNextLevel();
  } else if (lvl->getLives()==0) {
    // set global state to LOSE
    GAME_STATE = LOSE;
    rndr->saveScore(lvl->getScore());
    restartGame();
  }
}
void Controller::restartGame() {
  // reload first level
  currentLevel = -1;
  loadLevel(true, true);
}
void Controller::loadNextLevel() {
  // load next levelME;
  loadLevel(true);
}

void Controller::refreshDisplay() { rndr->refresh(); }

void Controller::loadLevel(bool next, bool reset) {
  if (loader->isEmpty()) {
    if (LOG)std::cerr<<"|Controller::loadLevel() -> No levels registered. Loading default level.\n";
    loader->loadDefault(lvl.get());
    return;
  }
  size_t index;
  if (next) {
    index = ((size_t)currentLevel+1) % loader->levelCount();
  } else {
    index = ((size_t)currentLevel-1+loader->levelCount()) % loader->levelCount();
  }
  try {
    loader->load(index,lvl.get(),reset);
    currentLevel = (int)index;
  } catch (const std::exception& err) {
    if (LOG)std::cerr<<"|Controller::loadLevel() -> Cannot load level of index {"<<index<<"}\n";
    loader->loadDefault(lvl.get());
  }
}

void Controller::reloadLevels() {
  loader->reloadFiles();
  try {
    loader->load((size_t)currentLevel,lvl.get(),true);
  } catch (const std::exception& err) {
    if (LOG)std::cerr<<"|Controller::loadLevel() -> Cannot load level of index {"<<currentLevel<<"}\n";
    loader->loadDefault(lvl.get());
  }
}
