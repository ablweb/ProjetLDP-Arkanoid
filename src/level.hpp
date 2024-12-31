#ifndef LEVEL_H
#define LEVEL_H

#include "entity.hpp"
#include "ball.hpp"
#include <memory>

class LevelManager {
private:
  // Here add all object of game, e.g. Brick, Ball, Palette, ...
  std::shared_ptr<TestRectangle> _palette;   // Raquette 
  std::shared_ptr<Ball> _ball;              // Balle
  std::vector<std::shared_ptr<TestRectangle>> _bricks; // Briques
  int _score;                             // Score du joueur
  int _lives;                              // Nombre de vies


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

};

#endif
