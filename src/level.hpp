#ifndef LEVEL_H
#define LEVEL_H

#include "entity.hpp"
<<<<<<< Updated upstream
#include "ball.hpp"
#include <memory>
=======
#include "env.hpp"
#include "utils.hpp"
>>>>>>> Stashed changes

class LevelManager {
private:
  // Here add all object of game, e.g. Brick, Ball, Palette, ...
  std::shared_ptr<TestRectangle> _palette;   // Raquette 
  std::shared_ptr<Ball> _ball;              // Balle
  std::vector<std::shared_ptr<TestRectangle>> _bricks; // Briques
  int _score;                             // Score du joueur
  int _lives;                              // Nombre de vies

<<<<<<< Updated upstream

public:
  LevelManager();
  ~LevelManager();

  // Here add all methode that the controller can call
  void movePaletteRigth();
  void movePaletteLeft();
  void update();

  // Méthodes pour le score
  int getScore() const; // Retourne le score
  void addScore(int points);
  int getLives() const;
  void loseLife();


  // Here add the inteface for the view acces
  std::shared_ptr<TestRectangle> getPalette() const;
  std::shared_ptr<Ball> getBall() const;
  std::vector<std::shared_ptr<TestRectangle>> getBricks() const;

=======
struct Level {
  // Here add all Game Entities
  std::unique_ptr<BrickHolder> bricks;
  std::unique_ptr<Paddle> paddle;
  std::unique_ptr<Ball> ball;

  int score = 0;  // Ajout du score
  Env* env = nullptr;  // Pointeur vers l'environnement


  // Also add them to the return vector of all()
  std::vector<Entity*> all() const;
  std::vector<CollisionGroup> getColisionMasks() const;

  // Getter pour le score
  int getScore() const { return score; }
};

class LevelLoader {
 private:
  Env* env = nullptr;  // Ajout du membre env
  std::vector<std::string> levelNames;
  std::vector<std::vector<BRICK_CONST::Param>> levelDatas;
  void registerLevelFiles();
  bool isValidLevelFormat(const std::string& levelPath);
  std::vector<BRICK_CONST::Param> extractLevelData(const std::string& levelPath);
 public:
  LevelLoader(Env* environment);
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
>>>>>>> Stashed changes
};

#endif
