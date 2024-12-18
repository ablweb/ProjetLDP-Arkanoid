#include "env.hpp"

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/display.h>
#include <allegro5/events.h>
#include <allegro5/keyboard.h>
#include <allegro5/system.h>
#include <allegro5/timer.h>

#include <stdexcept>

Env::Env() : FONT(nullptr), DISPLAY(nullptr), QUEUE(nullptr), TIMER(nullptr) {
  initAddons();
  createAssets();
  registerEvents();
  _isInit = true;
}

Env::~Env() {
  if (FONT) al_destroy_font(FONT);
  if (DISPLAY) al_destroy_display(DISPLAY);
  if (QUEUE) al_destroy_event_queue(QUEUE);
  if (TIMER) al_destroy_timer(TIMER);
  al_uninstall_keyboard();
}

bool Env::isInitialized() { return _isInit; }

void Env::initAddons() {
  // initialize addons
  if (!al_init())
    throw std::runtime_error("Error while initializing Allegro\n");
  if (!al_init_primitives_addon()) 
    throw std::runtime_error("Error while initializing primitives addon\n");
  if (!al_init_font_addon())
    throw std::runtime_error("Error while initializing font addon\n");
  if (!al_init_ttf_addon())
    throw std::runtime_error("Error while initializing ttf addon\n");
  if (!al_install_keyboard())
    throw std::runtime_error("Error while initializing keyboard\n");
}

void Env::createAssets() {
  // initialize assets
  DISPLAY = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
  if (!DISPLAY) throw std::runtime_error("Error while creating display");
  FONT = al_load_ttf_font(FONT_PATH, FONT_SIZE, 0);

  if (!FONT) throw std::runtime_error("Error while loading font");
  QUEUE = al_create_event_queue();

  if (!QUEUE) throw std::runtime_error("Error while creating queue");
  TIMER = al_create_timer(TIMER_RATE);

  if (!TIMER) throw std::runtime_error("Error while creating timer");
}

void Env::registerEvents() {
  // Enregistrement des sources d'événements
  al_register_event_source(QUEUE, al_get_keyboard_event_source());
  al_register_event_source(QUEUE, al_get_display_event_source(DISPLAY));
  al_register_event_source(QUEUE, al_get_timer_event_source(TIMER));
}

void Env::cleanup() {
  // Libération des ressources dans l'ordre inverse de leur création
  if (TIMER) {
    al_destroy_TIMER(TIMER);
    TIMER = nullptr;
  }
  if (QUEUE) {
    al_destroy_eventQUEUE(QUEUE);
    QUEUE = nullptr;
  }
  if (FONT) {
    al_destroyFONT(FONT);
    FONT = nullptr;
  }
  if (DISPLAY) {
    al_destroyDISPLAY(DISPLAY);
    DISPLAY = nullptr;
  }
  al_uninstall_keyboard();
}