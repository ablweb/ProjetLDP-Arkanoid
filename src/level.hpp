#ifndef LEVEL_H
#define LEVEL_H

#include <memory>
#include <string>
#include <sys/types.h>
#include <tuple>
#include <unordered_set>
#include <vector>

#include "entity.hpp"
#include "utils.hpp"

struct Level {
  // Here add all Game Entities
  std::unique_ptr<BrickHolder> bricks;
  // Also add them to the return tuple of all()
  auto all() const { return std::tie(bricks); }
};

class LevelLoader {
 private:
  std::vector<std::string> levelNames;
  std::vector<std::vector<BRICK_CONST::Param>> levelDatas;
  void registerLevelFiles();
  bool isValidLevelFormat(const std::string& levelPath);
  std::vector<BRICK_CONST::Param>
    extractLevelData(const std::string& levelPath);
 public:
  LevelLoader();
  ~LevelLoader();
  void load(size_t levelIndex, Level* lvl);
  void loadDefault(Level* lvl);
  size_t levelCount();
  bool isEmpty();
  void reloadFiles();
 private:
  const std::unordered_set<std::string> validColor = {
    "white","orange","cyan","green","red","blue","magenta","yellow","silver","gold"};
  const std::unordered_set<std::string> validBonus = {
    "none","laser","bigger","capture","slow","interruption","player"};
  bool validateRow(int row);
  bool validateCol(int col);
  bool validateColor(std::string color);
  bool validateBonus(std::string bonus);
};

#endif
