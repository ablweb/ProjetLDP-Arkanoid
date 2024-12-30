#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <allegro5/events.h>

#include <fstream>
#include <map>
#include <memory>
#include <vector>

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

  std::map<std::string,std::string> levelFiles;
  void registerLevelFiles();
  bool isValidLevelFormat(const std::string& levelPath);
  void loadJsonLevel(const std::string& levelPath);
  void loadDefaultLevel();
 public:
  Controller(StateManagerUPtr, RendererUPtr, LevelSPtr);
  ~Controller();

  int handleInput(const ALLEGRO_EVENT&);
  void refreshDisplay();
  void loadLevel();
};

#endif
