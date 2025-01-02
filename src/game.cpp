#include "game.hpp"

#include <allegro5/allegro_font.h>
#include <allegro5/color.h>
#include <allegro5/display.h>
#include <allegro5/events.h>

#include <memory>
#include <stdexcept>
#include <utility>

#include "env.hpp"
#include "controller.hpp"
#include "stateManager.hpp"
#include "renderer.hpp"
#include "level.hpp"

GameEngine::GameEngine() {
  checkEnv();
  generateController();
  running = true;
  run();
}

GameEngine::~GameEngine() {}

void GameEngine::checkEnv() {
  if (!env.isInitialized())
    throw std::runtime_error("Game environment not initialized");
}

void GameEngine::generateController() {
  auto lvl = std::make_shared<Level>();
  auto sm = std::make_unique<StateManager>(lvl);
  auto rndr = std::make_unique<Renderer>(lvl);
  controller =
      std::make_unique<Controller>(std::move(sm), std::move(rndr), lvl);
}

void GameEngine::run() {
  al_start_timer(env.TIMER);
  controller->loadLevel(1);
  while (running) {
    ALLEGRO_EVENT event;
    al_wait_for_event(env.QUEUE, &event);
    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      running = false;
    }
    if (event.type == ALLEGRO_EVENT_KEY_CHAR) {
      if (controller->handleInput(event) == -1) {
        running = false;
      }
    }
    if (event.type == ALLEGRO_EVENT_TIMER) {
      controller->refreshDisplay();
    }
  }
}
