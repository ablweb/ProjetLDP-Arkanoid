#ifndef INPUT_H
#define INPUT_H

#include "level.hpp"

#include <allegro5/events.h>
#include <memory>

class InputHandler {
private:
public:
  void handle(ALLEGRO_EVENT& event,std::shared_ptr<LevelManager> level, bool& running);
  InputHandler();
  ~InputHandler();
};

#endif
