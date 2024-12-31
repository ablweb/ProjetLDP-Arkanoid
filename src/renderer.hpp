#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include <string>
#include "entity.hpp"

class TestRectangle; // Déclaration avant inclusion pour réduire les dépendances

class Renderer {
private:
public:
  void drawTestRect(std::shared_ptr<TestRectangle> testRect);
  void drawScore(int score); // Afficher le score
  void drawLives(int lives);
  
  Renderer();
  ~Renderer();

  // Dessine un rectangle (utilisé pour tester ou afficher des entités)
  void drawTestRect(std::shared_ptr<TestRectangle> testRect);

  void refresh();
};

#endif // RENDERER_H