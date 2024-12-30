#ifndef GAME_H
#define GAME_H

#include <memory>

class Env;
class Controller;
class Level;

typedef std::unique_ptr<Env> EnvUPtr;
typedef std::unique_ptr<Controller> ControllerUPtr;

class GameEngine {
private:
  EnvUPtr env;
  ControllerUPtr controller;

  void checkEnv();
  void generateController();

  bool running;
  void run();
public:
  GameEngine(Env*);
  GameEngine(EnvUPtr);
  ~GameEngine();
};

#endif
