#ifndef ENV_H
#define ENV_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/events.h>
#include <allegro5/timer.h>

class Env {
private:
  bool _isInit;  // Indique si l'environnement est initialisé
  void initAddons();
  void createAssets();
  void registerEvents();
public:
  const int DISPLAY_WIDTH = 500;
  const int DISPLAY_HEIGHT = 500;
  const int FONT_SIZE = 20;
  const char* FONT_PATH = "resources/SourceCodePro-Regular.ttf";
  const double TIMER_RATE = 1.0/60;

  ALLEGRO_FONT* FONT;  // Police d'affichage
  ALLEGRO_DISPLAY* DISPLAY; // Fenêtre d'affichage
  ALLEGRO_EVENT_QUEUE* QUEUE;  // File d'attente d'événements
  ALLEGRO_TIMER* TIMER;  // Minuterie

  bool isInitialized();
  Env();
  ~Env();
};

#endif
