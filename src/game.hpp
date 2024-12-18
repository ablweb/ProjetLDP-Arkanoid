#ifndef GAME_H
#define GAME_H

#include "input.hpp"
#include "renderer.hpp"
#include "level.hpp"
#include <memory>

class Env;
class Renderer;
class InputHandler;

class GameManager {
private:
  std::unique_ptr<Env> gameEnv;
  std::unique_ptr<InputHandler> input;
  std::unique_ptr<Renderer> render;
  std::shared_ptr<LevelManager> level;

  bool running;
  void run();
public:
  GameManager(Env* gameEnv);
  ~GameManager();
};

#endif
