#include "controller.hpp"

#include <allegro5/keycodes.h>

#include <filesystem>
#include <iostream>
#include <memory>
#include <string>
#include <sys/types.h>
#include <unordered_set>
#include <utility>
#include <fstream>
#include "json.hpp"

#include "config.hpp"
#include "renderer.hpp"
#include "stateManager.hpp"
#include "level.hpp"
#include "utils.hpp"

using json = nlohmann::json;

Controller::Controller(StateManagerUPtr stateManager, RendererUPtr renderer,
                       LevelSPtr level)
    : sm(std::move(stateManager)), rndr(std::move(renderer)), lvl(level) {
  registerLevelFiles();
}

Controller::~Controller() {}

int Controller::handleInput(const ALLEGRO_EVENT& event) {
  int ret = 0;
  switch (event.keyboard.keycode) {
    case ALLEGRO_KEY_LEFT:
      std::cerr << "|Controller::handleInput() -> KEY_LEFT\n";
      sm->movePaddleLeft();
      break;
    case ALLEGRO_KEY_RIGHT:
      std::cerr << "|Controller::handleInput() -> KEY_RIGHT\n";
      sm->movePaddleRight();
      break;
    case ALLEGRO_KEY_N:
      std::cerr << "|Controller::handleInput() -> KEY_N\n";
      loadLevel();
      break;
    case ALLEGRO_KEY_X:
      std::cerr << "|Controller::handleInput() -> KEY_X\n";
      ret = -1; 
      break;
    default:
      break;
  }
  return ret;
}

void Controller::refreshDisplay() { rndr->refresh(); }

void Controller::loadLevel() {
  static auto currentLevel = levelFiles.begin();
  if (levelFiles.size() == 0) {
    loadDefaultLevel();
  } else {
    loadJsonLevel(currentLevel->first);
    if (++currentLevel == levelFiles.end()) {
      currentLevel = levelFiles.begin();
    }
  }
}

void Controller::loadDefaultLevel() { lvl->loadDefault(); }

void Controller::loadJsonLevel(const std::string& levelPath) {
  std::vector<BRICK_CONST::Param> bricksData;
  try {
    json j = json::parse(levelFiles[levelPath]);

    for (const auto& entry : j) {
      BRICK_CONST::Param p;
      p.row = entry["row"];
      p.col = entry["col"];
      p.color = BRICK_CONST::stringToCType.at(entry["color"]);
      p.bonus = BRICK_CONST::stringToBType.at(entry["bonus"]);
      bricksData.push_back(p);
    }
  } catch (const json::exception& err) {
    std::cerr << "Error whlie loading json file: " << err.what() << "\n";
  } catch (const std::exception& err) {
    std::cerr << "Error: " << err.what() << "\n";
  }
  lvl->loadCustom(bricksData, levelPath);
}

void Controller::registerLevelFiles() {
  // https://en.cppreference.com/w/cpp/filesystem/directory_iterator
  for (const auto& entry : std::filesystem::directory_iterator(LEVELS_DIR)) {
    std::string entryPath = entry.path().string();
    if (entry.is_regular_file() && isValidLevelFormat(entryPath)) {
      // https://www.quora.com/What-is-the-best-method-to-read-a-file-at-once-and-store-it-as-a-std-string-in-C++
      std::cerr << "|Controller::registerLevelFiles() -> " << entryPath << "\n";
      std::ifstream file(entryPath);
      std::stringstream fileContent; 
      fileContent << file.rdbuf();
      levelFiles[entryPath] = fileContent.str();
    }
  }
}

bool Controller::isValidLevelFormat(const std::string& levelPath) {
  // https://stackoverflow.com/questions/33628250/c-reading-a-json-object-from-file-with-nlohmann-json
  const std::unordered_set<std::string> validColor = {
    "white", "orange", "cyan", "green", "red", "blue", "magenta", "yellow",
    "silver", "gold"};
  const std::unordered_set<std::string> validBonus = {
    "none", "laser", "bigger", "capture", "slow", "interruption", "player"};
  try {
    int e = 0;
    std::ifstream file(levelPath);
    json j = json::parse(file);

    for (const auto& entry : j) {
      if (!entry.contains("row") || !entry.contains("col") || 
        !entry.contains("color") || !entry.contains("bonus")) {
        std::cerr<<"|Controller::isValidLevelFormat() -> In file {"<<levelPath<<"} In entry {"<<e<<"} missing information\n";
        return false;
      }
      if (!entry["row"].is_number_integer() ||
        entry["row"].get<int>() < 0 || entry["row"].get<int>() > 7) {
        std::cerr << "|Controller::isValidLevelFormat() -> In file {"<<levelPath<<"} In entry {" << e << "} row not formated correctly\n";
        return false;
      }
      if (!entry["col"].is_number_integer() ||
        entry["col"].get<int>() < 0 || entry["col"].get<int>() > 13) {
        std::cerr << "|Controller::isValidLevelFormat() -> In file {"<<levelPath<<"} In entry {" << e << "} col not formated correctly\n";
        return false;
      }
      if (!entry["color"].is_string() || !validColor.count(entry["color"].get<std::string>())) {
        std::cerr << "|Controller::isValidLevelFormat() -> In file {"<<levelPath<<"} In entry {" << e << "} color not formated correctly\n";
        return false;
      }
      if (!entry["bonus"].is_string() || !validBonus.count(entry["bonus"].get<std::string>())) {
        std::cerr << "|Controller::isValidLevelFormat() -> In file {"<<levelPath<<"} In entry {" << e << "} bonus not formated correctly\n";
        return false;
      }
      e++;
    }
  } catch (json::exception& err) {
    std::cerr << "Error whlie loading json file: " << err.what() << "\n";
    return false;
  } catch (const std::exception& err) {
    std::cerr << "Error: " << err.what() << "\n";
    return false;
  }
  return true;
}
