#include "level.hpp"

#include <cstddef>
#include <fcntl.h>
#include <fstream>
#include <filesystem>
#include <set>
#include <stdexcept>
#include <string>
#include <sys/types.h>

#include "json.hpp"
using json = nlohmann::json;

#include "config.hpp"

// -------------------------------------------------------------------------
// Level Loader
// -------------------------------------------------------------------------
LevelLoader::LevelLoader() {
  registerLevelFiles();
}
LevelLoader::~LevelLoader() {}

size_t LevelLoader::levelCount() { return levelDatas.size(); }
bool LevelLoader::isEmpty() { return levelDatas.empty(); }

void LevelLoader::load(size_t levelIndex, Level* lvl) {
  if (levelIndex >= levelCount()) { throw std::runtime_error("No level to load");}
  std::cerr<<"|Level::load -> Loading custom level {"<<levelNames[levelIndex]<<"}\n";
  lvl->bricks = std::make_unique<BrickHolder>(levelDatas[levelIndex]);
}

void LevelLoader::loadDefault(Level* lvl) {
  std::cerr<<"|Level::loadDefault -> Loading default level\n";
  lvl->bricks = std::make_unique<BrickHolder>();
  // Generate default level (tringular shape)
  using namespace BRICK_CONST;
  for (uint col = 1;col <= 12;++col) {
    int colorIndex = 50;
    uint start = 7;
    uint end = start - (col <= (12+1)/2 ? col - 1 : 12 - col);
    for (uint row = start;row >= end;--row) {
      lvl->bricks->addBrick({row, col, (colorType)colorIndex, none});
      colorIndex += 10;
    }
  }
}

void LevelLoader::reloadFiles() {
  std::cerr<<"|Controller::reloadFiles()\n";
  levelDatas.clear();
  levelNames.clear();
  registerLevelFiles();
}

// Iterate over a dir
// https://en.cppreference.com/w/cpp/filesystem/directory_iterator
// Sort fileSystem
// https://stackoverflow.com/questions/62409409/how-to-make-stdfilesystemdirectory-iterator-to-list-filenames-in-order
void LevelLoader::registerLevelFiles() {
  // Sort Files
  std::set<std::filesystem::path> sortedFiles;
  for (const auto& entry : std::filesystem::directory_iterator(LEVELS_DIR)) {
    if (entry.is_regular_file()) {
      sortedFiles.insert(entry.path());
    }
  }
  for (const auto& filePath : sortedFiles) {
    std::cerr<<"|Controller::registerLevelFiles() -> "<<filePath.string()<<"\n";
    if (isValidLevelFormat(filePath.string())) {
      std::vector<BRICK_CONST::Param> datas = extractLevelData(filePath.string());
      levelNames.push_back(filePath.string());
      levelDatas.push_back(datas);
    }
  }
}

// https://stackoverflow.com/questions/33628250/c-reading-a-json-object-from-file-with-nlohmann-json
bool LevelLoader::isValidLevelFormat(const std::string& levelPath) {
  std::ifstream file(levelPath);
  if (!file.is_open()) {
    std::cerr<<"Failed to open file: "<<levelPath<<"\n";
    return false;
  }
  int i = 1;
  try {
    json j = json::parse(file);
    for (auto& entry : j) {
      if (!entry["row"].is_number_integer() ||
          !entry["col"].is_number_integer() || 
          !entry["color"].is_string() ||
          !entry["bonus"].is_string()) {
        std::cerr<<"|Controller::isValidLevelFormat() -> Invalid entry type at {"
                 <<i<<"} in file {"<<levelPath<<"}\n";
        std::cerr<<HELP::LEVEL_JSON_FORMAT<<"\n";
        return false;
      }
      if (!validateRow(entry["row"]) ||
          !validateCol(entry["col"]) || 
          !validateColor(entry["color"]) ||
          !validateBonus(entry["bonus"])) {
        std::cerr<<"|Controller::isValidLevelFormat() -> Invalid entry format at {"
                 <<i<<"} in file {"<<levelPath<<"}\n";
        std::cerr<<HELP::LEVEL_JSON_FORMAT<<"\n";
        return false;
      }
      i++;
    }
  } catch (json::exception& err) {
    std::cerr<<"Error whlie loading json file: "<<err.what()<<"\n";
    return false;
  }
  return true;
}

bool LevelLoader::validateRow(int row) { return row >= 0 && row <= 7; }
bool LevelLoader::validateCol(int col) { return col >= 0 && col <= 13; }
bool LevelLoader::validateColor(std::string color) { return validColor.count(color); }
bool LevelLoader::validateBonus(std::string bonus) { return validBonus.count(bonus); }

// https://stackoverflow.com/questions/33628250/c-reading-a-json-object-from-file-with-nlohmann-json
std::vector<BRICK_CONST::Param> LevelLoader::extractLevelData(const std::string& levelPath) {
  std::vector<BRICK_CONST::Param> levelData;
  std::ifstream file(levelPath);
  try {
    json j = json::parse(file);
    for (const auto& entry : j) {
      BRICK_CONST::Param p;
      p.row = entry["row"];
      p.col = entry["col"];
      p.color = BRICK_CONST::stringToCType.at(entry["color"]);
      p.bonus = BRICK_CONST::stringToBType.at(entry["bonus"]);
      levelData.push_back(p);
    }
  } catch (const json::exception& err) {
    std::cerr<<"Error whlie loading json file: "<<err.what()<<"\n";
  }
  return levelData;
}
