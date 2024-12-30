#include "level.hpp"

#include <memory>

#include "entity.hpp"
#include "utils.hpp"

Level::Level() {}

void Level::loadDefault() {
  std::cerr << "|Level::loadDefault -> Loading default level\n";
  bricks = std::make_unique<BrickHolder>();
  using namespace BRICK_CONST;
  for (unsigned int col = 1;col <= 12;++col) {
    int colorIndex = 50;
    unsigned int start = 7;
    unsigned int end = start - (col <= (12+1)/2 ? col - 1 : 12 - col);
    for (unsigned int row = start;row >= end;--row) {
      bricks->addBrick({row, col, (colorType)colorIndex, none});
      colorIndex += 10;
    }
  }
}

void Level::loadCustom(const std::vector<BRICK_CONST::Param>& bricksData,
                       std::string levelName) {
  std::cerr << "|Level::loadCustom -> Loading custom level {" << levelName << "}\n";
  bricks = std::make_unique<BrickHolder>(bricksData);
}
