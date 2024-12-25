#include "controller.hpp"

#include <allegro5/keycodes.h>
#include <iostream>
#include <memory>
#include <utility>

#include "renderer.hpp"
#include "stateManager.hpp"

Controller::Controller(StateManagerUPtr stateManager,
                       RendererSPtr renderer)
  : sm(std::move(stateManager)),
    rndr(renderer) {
  sm->registerListener(rndr);
}

Controller::~Controller() {}

void Controller::handleInput(const ALLEGRO_EVENT& event) {
  if (event.type == ALLEGRO_EVENT_KEY_CHAR) {
    switch (event.keyboard.keycode) {
      case ALLEGRO_KEY_LEFT:
        std::cerr << "LEFT PRESSED";
        sm->movePaletteLeft();
        break;
      case ALLEGRO_KEY_RIGHT:
        std::cerr << "RIGHT PRESSED";
        sm->movePaletteRigth();
        break;
      default: break;
    }
  }
}

void Controller::render() {
  rndr->render(sm->getTestRect().get());
}
