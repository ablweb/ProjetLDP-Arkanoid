#include <iostream>
#include <stdexcept>

#include "env.hpp"
#include "game.hpp"
#include "utils.hpp"

int main() {
  using namespace RETURN_CODE;
  // check if any errors occured during allegro environment initialization
  try {
    env.init();
  } catch (const std::runtime_error& err) {
    env.cleanup();
    std::cerr << "Allegro: " << err.what() << std::endl;
    return ENVIRONMENT_SETUP_FAIL;
  }

  GameEngine* arkanoidGame = new GameEngine();

  delete arkanoidGame;
  arkanoidGame = nullptr;
  env.cleanup();
  return SUCCES;
}
