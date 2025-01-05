#include "controller.hpp"

#include <allegro5/keycodes.h>

#include <cstddef>
#include <exception>
#include <iostream>
#include <memory>
#include <sys/types.h>
#include <utility>

#include "level.hpp"
#include "env.hpp"
#include "renderer.hpp"
#include "stateManager.hpp"

Controller::Controller(StateManagerUPtr stateManager, RendererUPtr renderer,
                       LevelSPtr level)
    : sm(std::move(stateManager)), rndr(std::move(renderer)), lvl(level),
      loader(std::make_unique<LevelLoader>(new Env())),
      keyState(false), currentLevel(-1) {}

Controller::~Controller() {}

int Controller::handleInput(const ALLEGRO_EVENT& event) {
  int ret = 0;
  if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
    switch (event.keyboard.keycode) {
      case ALLEGRO_KEY_A:
        std::cerr<<"|Controller::handleInput() -> KEY_A_DOWN:LEFT\n";
        keyState[LEFT] = true; break;
      case ALLEGRO_KEY_Q:
        std::cerr<<"|Controller::handleInput() -> KEY_Q_DOWN:LEFT\n";
        keyState[LEFT] = true; break;
      case ALLEGRO_KEY_D:
        std::cerr<<"|Controller::handleInput() -> KEY_D_DOWN:RIGHT\n";
        keyState[RIGHT] = true; break;
      case ALLEGRO_KEY_P:
        std::cerr<<"|Controller::handleInput() -> KEY_P_DOWN:RIGHT\n";
        keyState[RIGHT] = true; break;
      case ALLEGRO_KEY_SPACE:
        std::cerr<<"|Controller::handleInput() -> KEY_SPACE_DOWN:ACTION\n";
        sm->launchBall(); break;
      case ALLEGRO_KEY_RIGHT:
        std::cerr<<"|Controller::handleInput() -> KEY_RIGHT_DOWN:NEXT\n";
        loadLevel(1); break;
      case ALLEGRO_KEY_LEFT:
        std::cerr<<"|Controller::handleInput() -> KEY_LEFT_DOWN:PREVIOUS\n";
        loadLevel(0); break;
      case ALLEGRO_KEY_R:
        std::cerr<<"|Controller::handleInput() -> KEY_R_DOWN:RELOAD\n";
        reloadLevels(); break;
      case ALLEGRO_KEY_ESCAPE:
        std::cerr<<"|Controller::handleInput() -> KEY_ESCAPE_DOWN:QUIT\n";
        ret = -1; break;
      default: break;
    }
  }
  if (event.type == ALLEGRO_EVENT_KEY_UP) {
    switch (event.keyboard.keycode) {
      case ALLEGRO_KEY_A:
        std::cerr<<"|Controller::handleInput() -> KEY_A_UP:LEFT\n";
        keyState[LEFT] = false; break;
      case ALLEGRO_KEY_Q:
        std::cerr<<"|Controller::handleInput() -> KEY_Q_UP:LEFT\n";
        keyState[LEFT] = false; break;
      case ALLEGRO_KEY_D:
        std::cerr<<"|Controller::handleInput() -> KEY_D_UP:RIGHT\n";
        keyState[RIGHT] = false; break;
      case ALLEGRO_KEY_P:
        std::cerr<<"|Controller::handleInput() -> KEY_P_UP:RIGHT\n";
        keyState[RIGHT] = false; break;
      default: break;
    }
  }
  handleContiniousKeyPress();
  return ret;
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
  // Vérifiez si toutes les briques ont été détruites
  if (sm->isVictory()) {
    // Affiche le message de victoire et attend une touche pour redémarrer
    rndr->drawVictoryMessage(lvl->getScore()); // Suppose que le score est dans `lvl`.
    ALLEGRO_EVENT event;
    do {
      al_wait_for_event(lvl->env->QUEUE, &event);
    }while (event.type != ALLEGRO_EVENT_KEY_DOWN);
    // Recharge le niveau ou démarre un nouveau jeu
    loadLevel(true); // Charge le prochain niveau ou redémarre.
  }
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
