#include "input.hpp"
#include "level.hpp"
#include <allegro5/events.h>
#include <allegro5/keycodes.h>

InputHandler::InputHandler() {}

InputHandler::~InputHandler() {}

void InputHandler::handle(ALLEGRO_EVENT& event, std::shared_ptr<LevelManager> level, bool& running) {
  if (event.type == ALLEGRO_EVENT_KEY_CHAR) {
    switch (event.keyboard.keycode) {
      case ALLEGRO_KEY_LEFT:
        level->movePaletteLeft(); 
        break;
      case ALLEGRO_KEY_RIGHT:
        level->movePaletteRigth();
        break;
    }
  }
  else if(event.type == ALLEGRO_EVENT_KEY_UP)
  {
    if(event.keyboard.keycode == ALLEGRO_KEY_X)
      running = false;
  }
}
