#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <allegro5/events.h>

#include <memory>

class StateManager;
class Renderer;
class Level;

typedef std::unique_ptr<StateManager> StateManagerUPtr;
typedef std::unique_ptr<Renderer> RendererUPtr;
typedef std::shared_ptr<Level> LevelSPtr;

class Controller {
 private:
  StateManagerUPtr sm;
  RendererUPtr rndr;
  LevelSPtr lvl;

 public:
  Controller(StateManagerUPtr, RendererUPtr, LevelSPtr);
  ~Controller();

  void handleInput(const ALLEGRO_EVENT&);
  void refreshDisplay();
};

#endif
