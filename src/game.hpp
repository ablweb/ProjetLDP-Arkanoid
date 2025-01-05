#ifndef GAME_H
#define GAME_H

#include <memory>

class Controller;
class Level;

typedef std::unique_ptr<Controller> ControllerUPtr;

class GameEngine {
private:
  ControllerUPtr controller;

  void checkEnv();
  void generateController();

  bool running;
  void run();
public:
  GameEngine();
  ~GameEngine();
};

#endif
