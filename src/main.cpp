#include <iostream>
#include <stdexcept>

#include "env.hpp"
#include "game.hpp"
#include "utils.hpp"

int main() {
  using namespace RETURN_CODE;
  Env* gameEnv;
  // check if any errors occured during allegro environment initialization
  try {
    gameEnv = new Env();
  } catch (const std::runtime_error& err) {
    std::cerr << "Allegro: " << err.what() << std::endl;
    return ENVIRONMENT_SETUP_FAIL;
  }

  GameManager* arkanoidGame = new GameManager(gameEnv);

  delete arkanoidGame;
  arkanoidGame = nullptr;
  // gameEnv is not deleted becaus its ownership is moved to a unique_ptr in GameManager 
  // TODO change that
  return SUCCES;
}
