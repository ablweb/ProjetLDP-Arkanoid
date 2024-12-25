#include <iostream>
#include <stdexcept>

#include "env.hpp"
#include "game.hpp"
#include "utils.hpp"

int main() {
  using namespace RETURN_CODE;
  std::unique_ptr<Env> gameEnv;
  // check if any errors occured during allegro environment initialization
  try {
    gameEnv = std::make_unique<Env>();
  } catch (const std::runtime_error& err) {
    std::cerr << "Allegro: " << err.what() << std::endl;
    return ENVIRONMENT_SETUP_FAIL;
  }

  GameEngine* arkanoidGame = new GameEngine(std::move(gameEnv));

  delete arkanoidGame;
  arkanoidGame = nullptr;
  return SUCCES;
}
