#include "controller.hpp"

#include <allegro5/keycodes.h>
#include <iostream>
#include <memory>
#include <utility>

#include "renderer.hpp"
#include "stateManager.hpp"

Controller::Controller(StateManagerUPtr stateManager,
                       RendererUPtr renderer,
                       LevelSPtr level)
  : sm(std::move(stateManager)),
    rndr(std::move(renderer)),
    lvl(level) {}

Controller::~Controller() {}

void Controller::handleInput(const ALLEGRO_EVENT& event) {
  switch (event.keyboard.keycode) {
    case ALLEGRO_KEY_LEFT:
      std::cerr << "|Controller::handleInput() -> KEY_LEFT\n";
      sm->movePaddleLeft();
      break;
    case ALLEGRO_KEY_RIGHT:
      std::cerr << "|Controller::handleInput() -> KEY_RIGHT\n";
      sm->movePaddleLeft();
      break;
    default: break;
  }
}

void Controller::refreshDisplay() {
  rndr->refresh();
}
