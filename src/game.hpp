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

  bool running; // État du jeu (en cours ou non)

  // Boucle principale du jeu
  void run();

public:
   // Constructeur
  GameManager(Env* gameEnv);

  // Destructeur
  ~GameManager();

  // Démarrer le jeu
  void start();

  // Arrêter le jeu
  void stop();

  // Vérifie si le jeu est en cours
  bool isRunning() const;
};

#endif
