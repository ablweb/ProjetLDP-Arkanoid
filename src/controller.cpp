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
#include "config.hpp"
#include "stateManager.hpp"

// Constructor to initialize Controller with state manager, renderer, and level
Controller::Controller(StateManagerUPtr stateManager, RendererUPtr renderer,
                       LevelSPtr level)
    : sm(std::move(stateManager)), rndr(std::move(renderer)), lvl(level),
      loader(std::make_unique<LevelLoader>()),
      keyState(false), currentLevel(-1) {}

Controller::~Controller() {}

// Handle input from the user (keyboard and mouse)
int Controller::handleInput() {
  int ret = 0; // Return value for special actions (like quitting)

  // Handle key press events
  if (env.EVENT.type == ALLEGRO_EVENT_KEY_DOWN) {
    // Transition from VICTORY or LOSE states back to IN_GAME
    if (GAME_STATE==VICTORY)GAME_STATE=IN_GAME;
    if (GAME_STATE==LOSE)GAME_STATE=IN_GAME;

    // Process specific key press events
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
      case ALLEGRO_KEY_Q:
        if (LOG_LEVEL>=3)std::cerr<<"|Controller::handleInput() -> KEY_Q_UP:LEFT\n";
        keyState[LEFT] = false; break;
      case ALLEGRO_KEY_D:
      case ALLEGRO_KEY_P:
        if (LOG_LEVEL>=3)std::cerr<<"|Controller::handleInput() -> KEY_P_UP:RIGHT\n";
        keyState[RIGHT] = false; break;
      default: break;
    }
  }
  if(MOUSE) handleMouse(); // if mouse handle is enabled
  handleContiniousKeyPress();
  return ret;
}
void Controller::handleMouse() { // Handles mouse movement to control the paddle
  if (env.MOUSE_STATE.x>(int)lvl->paddle->x() + LIMIT) {
    sm->movePaddleRight();
  } else if (env.MOUSE_STATE.x<(int)lvl->paddle->x() - LIMIT) {
    sm->movePaddleLeft();
  }
}

void Controller::handleContiniousKeyPress() {   // Handles continuous key presses for paddle movement
  if (keyState[LEFT]) { // If the left key is pressed, move the paddle left
    sm->movePaddleLeft(); 
  } else if (keyState[RIGHT]) { // If the right key is pressed, move the paddle right
    sm->movePaddleRight();
  }
}

void Controller::updateGameState(float deltaTime) {
  sm->update(deltaTime); 
}

// Checks the status (victory, lose) and acts accordignly
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
  currentLevel = -1; // Reset current level
  loadLevel(true, true); 
}
void Controller::loadNextLevel() {
  // load next level;
  loadLevel(true);
}
// Refresh the game display
void Controller::refreshDisplay() { 
  rndr->refresh();  // refresh the renderer's display
}

// Load a specific level (next or previous)
void Controller::loadLevel(bool next, bool reset) {
  if (loader->isEmpty()) {
    if (LOG)std::cerr<<"|Controller::loadLevel() -> No levels registered. Loading default level.\n";
    loader->loadDefault(lvl.get());
    return;
  }
  size_t index; // calculates the index of the level to load
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

void Controller::reloadLevels() { // Reload all levels from the file system
  loader->reloadFiles();  
  try {
    loader->load((size_t)currentLevel,lvl.get(),true);
  } catch (const std::exception& err) {
    if (LOG)std::cerr<<"|Controller::loadLevel() -> Cannot load level of index {"<<currentLevel<<"}\n";
    loader->loadDefault(lvl.get());
  }
}
