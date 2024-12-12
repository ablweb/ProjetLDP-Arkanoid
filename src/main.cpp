#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/display.h>

#include <iostream>
#include <stdexcept>

#include "env.hpp"
#include "game.hpp"

int main(int argc, char** argv) {
  Env gameEnv = Env();
  // check if any errors occured during allegro environment initialization
  try {
    gameEnv.init();
  } catch (const std::runtime_error& err) {
    std::cerr << "Allegro: " << err.what() << std::endl;
    return 1;
  }

  GameManager* arkanoidGame = new GameManager(&gameEnv);

  delete arkanoidGame;
  arkanoidGame = nullptr;
  return 0;
}
