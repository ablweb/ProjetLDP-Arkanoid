#ifndef ENV_H
#define ENV_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/events.h>

class Env {
private:
 void registerEvents();
public:
  const int DISPLAY_WIDTH = 500;
  const int DISPLAY_HEIGHT = 500;
  const int FONT_SIZE = 20;
  const char* FONT_PATH = "resources/SourceCodePro-Regular.ttf";

  ALLEGRO_FONT* FONT;
  ALLEGRO_DISPLAY* DISPLAY;
  ALLEGRO_EVENT_QUEUE* QUEUE;

  void init();
  Env();
  ~Env();
};

#endif
