#ifndef LEVEL_H
#define LEVEL_H

#include <memory>
#include <tuple>

#include "entity.hpp"
#include "utils.hpp"

struct Level {
  // Here add all Game Entities
  std::unique_ptr<TestRectangle> testRect;
  // Also add them to the return tuple of all()
  auto all() const { return std::tie(testRect); }
  // And initialise them in the contructor
  Level()
      : testRect(std::make_unique<TestRectangle>(tpl{100, 100}, 100, 100,
                                                 COLORS::RED)) {}
};

#endif
