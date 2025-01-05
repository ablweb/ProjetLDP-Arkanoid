#include <iostream>
#include <stdexcept>

#include "env.hpp"
#include "game.hpp"
#include "utils.hpp"

bool LOG = false;
uint LOG_LEVEL = 0;

bool MOUSE = false;

void parseArgs(int argc, char* argv[]) {
  // any args are given
  if (argc > 1) {
    for (int i = 1; i < argc; ++i) {
      std::string arg = argv[i];
      if (arg == "-l" || arg == "--log") {
        LOG = true;
        LOG_LEVEL = 1;
      }
      else if (arg.find("-l=", 0) == 0 || arg.find("--log=", 0) == 0) {
        LOG = true;
        try {
          int level = std::stoi(arg.substr(arg.find("=") + 1));
          LOG_LEVEL = (level >= 1 && level <= 3) ? (uint)level : 1;
        } catch (...) {
          LOG_LEVEL = 1; // Default to 2 if parsing fails
        }
      }
      else if (arg == "-m" || arg == "--mouse") {
        MOUSE = true;
      }
    }
  }
}

int main(int argc, char* argv[]) {
  using namespace RETURN_CODE;
  parseArgs(argc, argv);
  // check if any errors occured during allegro environment initialization
  try {
    env.init();
  } catch (const std::runtime_error& err) {
    env.cleanup();
    std::cerr<<"Allegro: "<<err.what()<<std::endl;
    return ENVIRONMENT_SETUP_FAIL;
  }

  GameEngine* arkanoidGame;
  try {
    arkanoidGame = new GameEngine();
  } catch (const std::exception& err) {
    std::cerr<<"Arkanoid: "<<err.what()<<std::endl;
    return GAME_RUNTIME_ERROR;
  }

  delete arkanoidGame;
  arkanoidGame = nullptr;
  env.cleanup();
  return SUCCES;
}
