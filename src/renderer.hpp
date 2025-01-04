#ifndef RENDERER_H
#define RENDERER_H

#include <memory>

class Entity;
class Level;
class BrickHolder;
class Brick;
class Paddle;
class Ball;

typedef std::shared_ptr<const Level> ConstLevelSPtr;

class Renderer {
 private:
  ConstLevelSPtr lvl;

 public:
  Renderer(ConstLevelSPtr);
  ~Renderer();
  void refresh();

  void drawBackground();
  void render(Entity*);
  void render(BrickHolder*);
  void render(Brick*);
  void render(Paddle*);
  void render(Ball*);
  // add new render methodes with other parameters
};

#endif
