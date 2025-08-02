#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>

class StateManager;
class Renderer;
class LevelLoader;
class Level;

typedef std::unique_ptr<StateManager> StateManagerUPtr;
typedef std::unique_ptr<Renderer> RendererUPtr;
typedef std::shared_ptr<Level> LevelSPtr;
typedef std::unique_ptr<LevelLoader> LevelLoaderUPtr;

enum KEYS{LEFT,RIGHT,ACTION,NEXT,PREVIOUS,RELOAD,QUIT};

/*
 * class Controller
 *
 * The Controller class is responsible for managing user inputs (keyboard and mouse),
 * interacting with the game state, and controlling the game's flow. It integrates
 * with the StateManager, Renderer, Level, and LevelLoader to process inputs, update
 * the game state, and manage levels. It encapsulates all input handling logic and 
 * ensures a seamless flow between game states.
 */
class Controller {
 private:
  StateManagerUPtr sm;
  RendererUPtr rndr;
  LevelSPtr lvl;
  LevelLoaderUPtr loader;

  bool keyState[7];
  void handleContiniousKeyPress();

  void restartGame();
  void loadNextLevel();
 public:
  Controller(StateManagerUPtr, RendererUPtr, LevelSPtr);
  ~Controller();

  int currentLevel;
  int handleInput();
  void handleMouse();
  void updateGameState(float deltaTime);
  void checkGameState();
  void refreshDisplay();
  void loadLevel(bool next, bool reset=false);
  void reloadLevels();
};

#endif
