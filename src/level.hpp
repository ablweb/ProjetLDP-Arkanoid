#ifndef LEVEL_H
#define LEVEL_H

#include <memory>
#include <tuple>

#include "entity.hpp"

class Level {
public:
  // Here add all Game Entities
  std::unique_ptr<BrickHolder> bricks;
  // Also add them to the return tuple of all()
  auto all() const { return std::tie(bricks); }
  // And initialise them in the contructor
  Level();
  void loadDefault();
  void loadCustom(const std::vector<BRICK_CONST::Param>&, std::string);
};

#endif
