#ifndef GAME_H
#define GAME_H

#include "input.hpp"
#include "scene.hpp"

class Env;
class Scene;
class InputHandler;

class GameManager {
 private:
  InputHandler _input;
  Scene _mainScene;
  bool _running;
  Env* _gameEnv;

  void gameLoop();
 public:
  GameManager(Env* gameEnv);
  ~GameManager();
};

#endif
