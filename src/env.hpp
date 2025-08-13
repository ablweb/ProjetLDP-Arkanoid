#ifndef ENV_H
#define ENV_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/events.h>
#include <allegro5/timer.h>

enum State{IN_GAME,VICTORY,LOSE};

// https://stackoverflow.com/questions/1008019/how-do-you-implement-the-singleton-design-pattern
// Singleton Design Pattern
class Env { 
 public:
  static Env& getInstance() { // Get the single instance of Env
    static Env instance; // Guaranteed to be destroyed.
    return instance; // Instantiated on first use.
  }
 private:
  bool _isInit;
  void initAddons();
  void createAssets();
  void registerEvents();

  Env() {};
 public:
  Env(Env const&)            = delete;
  void operator=(Env const&) = delete;

  ALLEGRO_FONT        * FONT;
  ALLEGRO_FONT        * FONT_HUGE;
  ALLEGRO_DISPLAY     * DISPLAY;
  ALLEGRO_EVENT_QUEUE * QUEUE;
  ALLEGRO_TIMER       * TIMER;

  ALLEGRO_EVENT       EVENT;
  ALLEGRO_MOUSE_STATE MOUSE_STATE;

  void init();
  void cleanup();
  bool isInitialized();
};

// Globally accesible Env when including env.hpp
extern Env& env;

extern State GAME_STATE;

#endif
