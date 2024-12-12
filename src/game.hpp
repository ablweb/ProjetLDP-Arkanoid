#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "input.hpp"
#include "scene.hpp"

class Env;
class Scene;
class InputHandler;

class GameManager {
 private:
  InputHandler input;
  Scene mainScene;
  bool running;
  Env* _gameEnv;

  void gameLoop();

 public:
  GameManager(Env* gameEnv);
  ~GameManager();
};

#endif
