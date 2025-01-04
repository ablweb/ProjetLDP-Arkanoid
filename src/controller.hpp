#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <allegro5/events.h>

#include <memory>

class StateManager;
class Renderer;
class LevelLoader;
struct Level;

typedef std::unique_ptr<StateManager> StateManagerUPtr;
typedef std::unique_ptr<Renderer> RendererUPtr;
typedef std::shared_ptr<Level> LevelSPtr;
typedef std::unique_ptr<LevelLoader> LevelLoaderUPtr;

enum KEYS{LEFT,RIGHT,ACTION,NEXT,PREVIOUS,RELOAD,QUIT};

class Controller {
 private:
  StateManagerUPtr sm;
  RendererUPtr rndr;
  LevelSPtr lvl;
  LevelLoaderUPtr loader;

  bool keyState[7];
  void handleContiniousKeyPress();
 public:
  Controller(StateManagerUPtr, RendererUPtr, LevelSPtr);
  ~Controller();

  int currentLevel;
  int handleInput(const ALLEGRO_EVENT&);
  void updateGameState();
  void refreshDisplay();
  void loadLevel(bool next);
  void reloadLevels();
};

#endif
