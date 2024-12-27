#ifndef ENV_H
#define ENV_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/events.h>
#include <allegro5/timer.h>

class Env {
 private:
  bool _isInit;
  void initAddons();
  void createAssets();
  void registerEvents();

 public:
  const int DISPLAY_WIDTH = 500;
  const int DISPLAY_HEIGHT = 500;
  const int FONT_SIZE = 20;
  const char* FONT_PATH = "resources/SourceCodePro-Regular.ttf";
  const double FRAME_RATE = 1.0 / 60;

  ALLEGRO_FONT* FONT;
  ALLEGRO_DISPLAY* DISPLAY;
  ALLEGRO_EVENT_QUEUE* QUEUE;
  ALLEGRO_TIMER* TIMER;

  bool isInitialized();
  Env();
  ~Env();
};

#endif
