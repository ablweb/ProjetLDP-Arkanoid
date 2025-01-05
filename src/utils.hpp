#ifndef UTILS_H
#define UTILS_H

#include "config.hpp"
#include <allegro5/color.h>

#include <iostream>
#include <string>
#include <unordered_map>

struct tpl {
  float x = 0, y = 0;
};

namespace RETURN_CODE {
enum { SUCCES, ENVIRONMENT_SETUP_FAIL, GAME_RUNTIME_ERROR };
};  // namespace RETURN_CODE

namespace HELP {
inline const std::string LEVEL_JSON_FORMAT = 
  "HELP: LEVEL_JSON_FORMAT\n"
  "The level JSON format should be an array of objects, each representing a tile in the level. Each tile must contain the following fields:\n"
  "  - 'row' (integer): The row number of the tile (0 <= row <= 7).\n"
  "  - 'col' (integer): The column number of the tile (0 <= col <= 13).\n"
  "  - 'color' (string): The color of the tile. Allowed values: 'white', 'orange', 'cyan', 'green', 'red', 'blue', 'magenta', 'yellow', 'silver', 'gold'.\n"
  "  - 'bonus' (string): The bonus on the tile. Allowed values: 'none', 'laser', 'bigger', 'capture', 'slow', 'interruption', 'player'.\n"
  "Example:\n"
  "[\n"
  "  {\"row\": 0, \"col\": 0, \"color\": \"cyan\", \"bonus\": \"none\"},\n"
  "  {\"row\": 1, \"col\": 1, \"color\": \"green\", \"bonus\": \"laser\"}\n"
  "]\n"
  "Make sure all values are within the allowed ranges and use valid strings for color and bonus.\n";
inline const std::string DISPLAY_KEY_INFO = 
  "Controls:\n"
  "D / P      - Move paddle right  |  R           - Reload level files\n"
  "A / Q      -  Move paddle left  |  RIGHT ARROW -     Previous level\n"
  "SPACE      -   Launch the ball  |  LEFT ARROW  -         Next level\n"
  "ESCAPE     -     Quit the game  |\n";
}; // namespace HELP

namespace COLORS {
const ALLEGRO_COLOR BLACK    = al_map_rgb(0,0,0);
const ALLEGRO_COLOR WHITE    = al_map_rgb(255,255,255);
const ALLEGRO_COLOR ORANGE   = al_map_rgb(255,165,0);
const ALLEGRO_COLOR CYAN     = al_map_rgb(0,255,255);
const ALLEGRO_COLOR GREEN    = al_map_rgb(0,255,0);
const ALLEGRO_COLOR GREEN_B  = al_map_rgb(0,255,100);
const ALLEGRO_COLOR RED      = al_map_rgb(255,0,0);
const ALLEGRO_COLOR BLUE     = al_map_rgb(0,0,255);
const ALLEGRO_COLOR MAGENTA  = al_map_rgb(255,0,255);
const ALLEGRO_COLOR YELLOW   = al_map_rgb(255,255,0);
const ALLEGRO_COLOR YELLOW_B = al_map_rgb(239,191,4);
const ALLEGRO_COLOR GREY     = al_map_rgb(212,212,212);
const ALLEGRO_COLOR GREY_B   = al_map_rgb(178,178,178);
const ALLEGRO_COLOR FONT_C   = BLACK;
};  // namespace COLORS

namespace Game {
enum State{IN_GAME,VICTORY,LOSE};
}

namespace BRICK_CONST {
constexpr float width = 40.0;
constexpr float height = 20.0; 
constexpr float spacing = 3.0;
enum colorType {
  white=50,
  orange=60,
  cyan=70,
  green=80,
  red=90,
  blue=100,
  magenta=110, yellow=120,
  silver=200,
  gold=-1
};
const std::unordered_map<std::string, colorType>
stringToCType {
  {"white", white},
  {"orange", orange},
  {"cyan", cyan},
  {"green", green},
  {"red", red},
  {"blue", blue},
  {"magenta", magenta},
  {"yellow", yellow},
  {"silver", silver},
  {"gold", gold}
};
enum bonusType {
  none=0,
  laser,
  bigger,
  capture,
  slow,
  interruption,
  player
};
const std::unordered_map<std::string, bonusType>
stringToBType {
  {"none", none},
  {"laser", laser},
  {"bigger", bigger},
  {"capture", capture},
  {"slow", slow},
  {"interruption", interruption},
  {"player", player},
};
using namespace COLORS;
const std::unordered_map<colorType, ALLEGRO_COLOR>
typeToColor {
  {white, WHITE},
  {orange, ORANGE},
  {cyan, CYAN},
  {green, GREEN},
  {red, RED},
  {blue, BLUE},
  {magenta, MAGENTA},
  {yellow, YELLOW},
  {silver, GREY_B},
  {gold, YELLOW_B}
};
struct Param {
  unsigned int row;
  unsigned int col;
  colorType color;
  bonusType bonus;
};
}; // Brick

namespace PADDLE_CONST { 
constexpr float spawnWidth = 100.0;
constexpr float spawnHeight = 15.0; 
constexpr tpl spawnPosition = {
  ((float)DISPLAY_WIDTH/2),
  ((float)DISPLAY_HEIGHT)-GAME_TOP_MARGIN/1.5
};
constexpr float normalSpeed = 6.0; 
const ALLEGRO_COLOR normalColor = COLORS::WHITE;
} // PADDLE_CONST

namespace BALL_CONST { 
constexpr float baseRadius = 10.0; 
constexpr tpl spawnPosition = {
  PADDLE_CONST::spawnPosition.x,
  PADDLE_CONST::spawnPosition.y-baseRadius*2
};
constexpr float baseSpeed = 6.0; 
constexpr float maxSpeed = 12.0; 
constexpr int bounceModulo = 15; // Bounce before speed increases
constexpr float deadzone = 20.0; // deadzone from bottom of game view
const ALLEGRO_COLOR normalColor = COLORS::GREEN_B;
} // PADDLE_CONST

#endif
