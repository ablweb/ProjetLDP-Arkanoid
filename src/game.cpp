#include "game.hpp"

#include <allegro5/allegro_font.h>
#include <allegro5/color.h>
#include <allegro5/display.h>
#include <allegro5/events.h>

#include "env.hpp"
#include "utils.hpp"

using namespace COLORS;

GameManager::GameManager(Env* gameEnv) : _gameEnv(gameEnv) { gameLoop(); }

GameManager::~GameManager() {}

void GameManager::gameLoop() {
  while (running) {
    ALLEGRO_EVENT event;
    al_wait_for_event(_gameEnv->QUEUE, &event);
    if (event.type == ALLEGRO_EVENT_KEY_UP || event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      running = false;
    }
    al_flip_display();
  }
}
