#ifndef GAME_H
#define GAME_H

#include <memory>

class Env;
class Controller;

typedef std::unique_ptr<Env> EnvUPtr ;

class GameEngine {
private:
  std::unique_ptr<Env> env;
  std::unique_ptr<Controller> controller;

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
