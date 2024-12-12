#include "game.hpp"

#include <allegro5/allegro_font.h>
#include <allegro5/color.h>
#include <allegro5/display.h>
#include <allegro5/events.h>

#include <stdexcept>

#include "env.hpp"
#include "utils.hpp"
#include "entity.hpp"

GameManager::GameManager(Env* gameEnv) : _gameEnv(gameEnv) { 
  if (!gameEnv->isInitialized())
    throw std::runtime_error("Game environment not initialized");
  gameLoop(); 
}

GameManager::~GameManager() {}

void GameManager::gameLoop() {
  TestRectangle test = TestRectangle(tpl{100, 100}, 100, 100, COLORS::RED);
  while (_running) {
    ALLEGRO_EVENT event;
    al_start_timer(_gameEnv->TIMER);
    al_wait_for_event(_gameEnv->QUEUE, &event);
    if (event.type == ALLEGRO_EVENT_KEY_UP || event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      _running = false;
    }
    if (event.type == ALLEGRO_EVENT_TIMER) {
      al_clear_to_color(al_map_rgb(255, 255, 255));
      test.draw();
      al_flip_display();
    }
  }
}
