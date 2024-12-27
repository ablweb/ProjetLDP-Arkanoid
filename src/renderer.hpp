#ifndef RENDERER_H
#define RENDERER_H

#include <memory>

class Entity;
class TestRectangle;
class Level;

typedef std::shared_ptr<const Level> ConstLevelSPtr;

class Renderer {
private:
  ConstLevelSPtr lvl;
public:
  Renderer(ConstLevelSPtr);
  ~Renderer();
  void refresh();

  void renderType(Entity*);
  void render(TestRectangle*);
  // add new render methodes with other parameters
};

#endif
