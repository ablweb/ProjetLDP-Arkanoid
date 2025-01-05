#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include <string>
#include "entity.hpp"

<<<<<<< Updated upstream
class TestRectangle; // Déclaration avant inclusion pour réduire les dépendances
=======
class Entity;
struct Level;
class BrickHolder;
class Brick;
class Paddle;
class Ball;

typedef std::shared_ptr<const Level> ConstLevelSPtr;
>>>>>>> Stashed changes

class Renderer {
private:
public:
  void drawTestRect(std::shared_ptr<TestRectangle> testRect);
  void drawScore(int score); // Afficher le score
  void drawLives(int lives);
  
  Renderer();
  ~Renderer();

<<<<<<< Updated upstream
  // Dessine un rectangle (utilisé pour tester ou afficher des entités)
  void drawTestRect(std::shared_ptr<TestRectangle> testRect);

  void refresh();
=======
  void drawBackground();
  void render(Entity*);
  void render(BrickHolder*);
  void render(Brick*);
  void render(Paddle*);
  void render(Ball*);
  // add new render methodes with other parameters

  void drawVictoryMessage(int score);

>>>>>>> Stashed changes
};

#endif // RENDERER_H