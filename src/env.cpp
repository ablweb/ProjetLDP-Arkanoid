#include "env.hpp"

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/display.h>
#include <allegro5/keyboard.h>
#include <allegro5/mouse.h>
#include <allegro5/system.h>

#include <stdexcept>

#include "config.hpp"

Env& env = Env::getInstance();
State GAME_STATE = IN_GAME;

void Env::init() { // Initialize the environment
  FONT = nullptr;
  FONT_HUGE = nullptr;
  DISPLAY = nullptr;
  QUEUE = nullptr;
  TIMER = nullptr;
  initAddons();
  createAssets();
  registerEvents();
  _isInit = true;
}

void Env::cleanup() { // Cleanup the environment
  if (FONT) al_destroy_font(FONT);
  if (FONT_HUGE) al_destroy_font(FONT_HUGE);
  if (DISPLAY) al_destroy_display(DISPLAY);
  if (QUEUE) al_destroy_event_queue(QUEUE);
  if (TIMER) al_destroy_timer(TIMER);
  al_uninstall_keyboard();
  al_uninstall_mouse();
}

bool Env::isInitialized() { return _isInit; } // Check if the environment is initialized

void Env::initAddons() { // Initialize Allegro addons
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
  if (!al_install_mouse())
    throw std::runtime_error("Error while initializing mouse\n");
}

void Env::createAssets() {
  DISPLAY = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
  if (!DISPLAY) throw std::runtime_error("Error while creating display");
  FONT = al_load_ttf_font(FONT_PATH, FONT_SIZE, 0);
  if (!FONT) throw std::runtime_error("Error while loading font");
  FONT_HUGE = al_load_ttf_font(FONT_PATH, FONT_SIZE*2, 0);
  if (!FONT_HUGE) throw std::runtime_error("Error while loading font");
  QUEUE = al_create_event_queue();
  if (!QUEUE) throw std::runtime_error("Error while creating queue");
  TIMER = al_create_timer(FRAME_RATE);
  if (!TIMER) throw std::runtime_error("Error while creating timer");
}

void Env::registerEvents() {
  al_register_event_source(QUEUE, al_get_keyboard_event_source());
  al_register_event_source(QUEUE, al_get_display_event_source(DISPLAY));
  al_register_event_source(QUEUE, al_get_timer_event_source(TIMER));
}
