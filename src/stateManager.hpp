#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <memory>

#include "utils.hpp"

class Entity;
class TestRectangle;

typedef std::shared_ptr<TestRectangle> TestRectSPtr ;

class StateManager : public Notifier<Entity> {
private:
  // Here add all object of game, e.g. Brick, Ball, Palette, ...
  TestRectSPtr testRect;
public:
  StateManager();
  ~StateManager();

  // Here add all methode that the controller can call
  void movePaletteRigth();
  void movePaletteLeft();
  void update();

  // Here add the inteface for the view acces
  TestRectSPtr getTestRect() const;
};


#endif
