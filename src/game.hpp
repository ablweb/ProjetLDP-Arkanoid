#ifndef GAME_H
#define GAME_H

#include <memory>

class Env;
class Controller;

class GameEngine {
private:
  std::unique_ptr<Env> env;
  std::unique_ptr<Controller> controller;

  void checkEnv();
  void generateController();

  bool running;
  void run();
public:
  GameEngine(Env* gameEnv);
  GameEngine(std::unique_ptr<Env> gameEnv);
  ~GameEngine();
};

#endif
