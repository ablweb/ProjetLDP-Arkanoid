#include "controller.hpp"

#include <allegro5/keycodes.h>

#include <cstddef>
#include <exception>
#include <iostream>
#include <memory>
#include <sys/types.h>
#include <utility>

#include "level.hpp"
#include "renderer.hpp"
#include "stateManager.hpp"

Controller::Controller(StateManagerUPtr stateManager, RendererUPtr renderer,
                       LevelSPtr level)
    : sm(std::move(stateManager)), rndr(std::move(renderer)), lvl(level),
      loader(std::make_unique<LevelLoader>()), currentLevel(-1) {}

Controller::~Controller() {}

int Controller::handleInput(const ALLEGRO_EVENT& event) {
  int ret = 0;
  switch (event.keyboard.keycode) {
    case ALLEGRO_KEY_LEFT:
      std::cerr << "|Controller::handleInput() -> KEY_LEFT\n";
      sm->movePaddleLeft();
      break;
    case ALLEGRO_KEY_RIGHT:
      std::cerr << "|Controller::handleInput() -> KEY_RIGHT\n";
      sm->movePaddleRight();
      break;
    case ALLEGRO_KEY_N:
      std::cerr << "|Controller::handleInput() -> KEY_N\n";
      loadLevel(1);
      break;
    case ALLEGRO_KEY_P:
      std::cerr << "|Controller::handleInput() -> KEY_P\n";
      loadLevel(0);
      break;
    case ALLEGRO_KEY_R:
      std::cerr << "|Controller::handleInput() -> KEY_R\n";
      reloadLevels();
      break;
    case ALLEGRO_KEY_X:
      std::cerr << "|Controller::handleInput() -> KEY_X\n";
      ret = -1; 
      break;
    default:
      break;
  }
  return ret;
}

void Controller::refreshDisplay() { rndr->refresh(); }

void Controller::loadLevel(bool next) {
  if (loader->isEmpty()) {
    std::cerr<<"|Controller::loadLevel() -> No levels registered. Loading default level.\n";
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
    loader->load(index,lvl.get());
    currentLevel = (int)index;
  } catch (const std::exception& err) {
    std::cerr<<"|Controller::loadLevel() -> Cannot load level of index {"<<index<<"}\n";
    loader->loadDefault(lvl.get());
  }
}

void Controller::reloadLevels() {
  loader->reloadFiles();
  try {
    loader->load((size_t)currentLevel,lvl.get());
  } catch (const std::exception& err) {
    std::cerr<<"|Controller::loadLevel() -> Cannot load level of index {"<<currentLevel<<"}\n";
    loader->loadDefault(lvl.get());
  }
}
