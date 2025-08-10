#ifndef GAME_H
#define GAME_H

#include <memory>

class Controller;
class Level;

typedef std::unique_ptr<Controller> ControllerUPtr;

class GameEngine { // Main game engine class that manages the game loop and controller
private:
  ControllerUPtr controller; // Controller that handles game logic

  void checkEnv(); // Check if the environment is initialized
  void generateController(); // Generate the controller for the game

  bool running;
  void run();
public:
  GameEngine();
  ~GameEngine();
};

#endif
