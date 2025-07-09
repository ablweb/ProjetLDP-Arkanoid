#ifndef RENDERER_H
#define RENDERER_H

#include <memory>

class Entity;
class Level;
class BrickHolder;
class Brick;
class Paddle;
class Ball;
class Bonus;


typedef std::shared_ptr<const Level> ConstLevelSPtr;

class Renderer {
 private:
  ConstLevelSPtr lvl;
  int _savedScore; // save the last score before lose

 public:
  Renderer(ConstLevelSPtr);
  ~Renderer();

  void saveScore(int);

  void refresh();

  void render(Entity*);
  void render(BrickHolder*);
  void render(Brick*);
  void render(Paddle*);
  void render(Ball*);
  void render(Bonus*);

  void drawVictoryMessage();
  void drawLoseMessage();
  // add new render methodes with other parameters
 private:
  void drawBackground();
  void drawGameInfo();
  void drawScore();
  void drawLevelName();
  void drawRemainingLives();
  void drawKeyInfo();
};

#endif
