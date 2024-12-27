#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <memory>

class Entity;
class Level;

typedef std::shared_ptr<Level> LevelSPtr;

class StateManager {
private:
  LevelSPtr lvl;
public:
  StateManager(LevelSPtr);
  ~StateManager();

  // Here add all methode to change state of game assets
  void movePaletteRigth();
  void movePaletteLeft();
  void update();
};

#endif
