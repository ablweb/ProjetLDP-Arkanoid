#ifndef LEVEL_H
#define LEVEL_H

#include "entity.hpp"
#include <memory>

class LevelManager {
private:
  // Here add all object of game, e.g. Brick, Ball, Palette, ...
  std::shared_ptr<TestRectangle> testRect;
public:
  LevelManager();
  ~LevelManager();

  // Here add all methode that the controller can call
  void movePaletteRigth();
  void movePaletteLeft();
  void update();

  // Here add the inteface for the view acces
  std::shared_ptr<TestRectangle> getTestRect() const;
};

#endif
