#include "game.hpp"

#include <allegro5/allegro_font.h>
#include <allegro5/color.h>
#include <allegro5/display.h>
#include <allegro5/events.h>

#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>

#include "env.hpp"
#include "controller.hpp"
#include "stateManager.hpp"
#include "renderer.hpp"

GameEngine::GameEngine(std::unique_ptr<Env> gameEnv)
  : env(std::move(gameEnv)) {
  checkEnv();
  generateController();
  running = true;
  run(); 
}

GameEngine::GameEngine(Env* gameEnv)
  : env(gameEnv) {
  checkEnv();
  generateController();
  running = true;
  run(); 
}

GameEngine::~GameEngine() {}

void GameEngine::checkEnv() {
  if (!env->isInitialized())
    throw std::runtime_error("Game environment not initialized");
}

void GameEngine::generateController() {
  auto sm = std::make_unique<StateManager>();
  auto ren = std::make_shared<Renderer>();
  controller = std::make_unique<Controller>(std::move(sm), ren);
}

void GameEngine::run() {
  while (running) {
    ALLEGRO_EVENT event;
    al_start_timer(env->TIMER);
    al_wait_for_event(env->QUEUE, &event);
    controller->handleInput(event);
    if (event.type == ALLEGRO_EVENT_TIMER) {
      al_clear_to_color(al_map_rgb(255, 255, 255));
      controller->render();
      al_flip_display();
    }
  }
}
