#include "game.hpp"

#include <allegro5/allegro_font.h>
#include <allegro5/color.h>
#include <allegro5/display.h>
#include <allegro5/events.h>

#include <memory>
#include <stdexcept>

#include "env.hpp"
#include "input.hpp"
#include "level.hpp"
#include "renderer.hpp"

// Constructeur
GameManager::GameManager(Env* gameEnv)
  : gameEnv(gameEnv),
    input(std::make_unique<InputHandler>()),
    render(std::make_unique<Renderer>()),  
    level(std::make_shared<LevelManager>()) {
  if (!gameEnv->isInitialized())
    throw std::runtime_error("Game environment not initialized");
  running = true;
  run(); 
}
// Destructeur
GameManager::~GameManager() {}

// Méthode pour démarrer le jeu
void GameManager::run() {
  while (running) {
    ALLEGRO_EVENT event;
    al_start_timer(gameEnv->TIMER);
    al_wait_for_event(gameEnv->QUEUE, &event);

    // Gestion des entrées utilisateur
    input->handle(event, level, running);


    if (event.type == ALLEGRO_EVENT_TIMER) {
      al_clear_to_color(al_map_rgb(255, 255, 255));
      render->drawTestRect(level->getPalette());
      al_flip_display();
    }
  }
}
