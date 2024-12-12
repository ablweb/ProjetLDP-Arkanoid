#include "env.hpp"

#include <allegro5/allegro_font.h>
#include <allegro5/display.h>
#include <allegro5/events.h>
#include <allegro5/keyboard.h>
#include <allegro5/system.h>

#include <cstdio>
#include <stdexcept>

Env::Env() : FONT(nullptr), DISPLAY(nullptr) {}

Env::~Env() {
  if (FONT) al_destroy_font(FONT);
  if (DISPLAY) al_destroy_display(DISPLAY);
  if (QUEUE) al_destroy_event_queue(QUEUE);
  al_uninstall_keyboard();
}

void Env::init() {
  // initialize addons
  if (!al_init())
    throw std::runtime_error("Error while initializing Allegro\n");
  if (!al_init_font_addon())
    throw std::runtime_error("Error while initializing font addon\n");
  if (!al_init_ttf_addon())
    throw std::runtime_error("Error while initializing ttf addon\n");
  if (!al_install_keyboard())
    throw std::runtime_error("Error while initializing keyboard\n");

  // initialize assets
  DISPLAY = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
  if (!DISPLAY) throw std::runtime_error("Error while creating display");
  FONT = al_load_ttf_font(FONT_PATH, FONT_SIZE, 0);
  if (!FONT) throw std::runtime_error("Error while loading font");
  QUEUE = al_create_event_queue();
  if (!QUEUE) throw std::runtime_error("Error while creating queue");
  registerEvents();
}

void Env::registerEvents() {
  al_register_event_source(QUEUE, al_get_keyboard_event_source());
  al_register_event_source(QUEUE, al_get_display_event_source(DISPLAY));
}
