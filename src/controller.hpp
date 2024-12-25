#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <allegro5/events.h>
#include <memory>

class StateManager;
class Renderer;

typedef std::unique_ptr<StateManager> StateManagerUPtr ;
typedef std::shared_ptr<Renderer> RendererSPtr ;

class Controller {
private:
  StateManagerUPtr  sm;
  RendererSPtr  rndr;

public:
  Controller(StateManagerUPtr stateManager,
             RendererSPtr renderer);
  ~Controller();

  void handleInput(const ALLEGRO_EVENT& event);
  void render();
};

#endif
