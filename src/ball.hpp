#ifndef BALL_H
#define BALL_H

#include "entity.hpp" // Pour hériter de TestRectangle
#include <allegro5/color.h>

class Ball : public TestRectangle {
private:
  float _dx;     // Direction horizontale (valeurs entre -1 et 1)
  float _dy;     // Direction verticale (valeurs entre -1 et 1)
  float _speed;  // Vitesse de déplacement de la balle

public:
  // Constructeur
  Ball(tpl position, float width, float height, ALLEGRO_COLOR color, float speed);

  // Déplace la balle en fonction de sa direction et de sa vitesse
  void move();

  // Change la direction horizontale (rebond latéral)
  void bounceHorizontal();

  // Change la direction verticale (rebond haut/bas)
  void bounceVertical();

  // Définit une nouvelle direction
  void setDirection(float dx, float dy);

  // Getters pour la direction
  float dx() const;
  float dy() const;

  // Getter et setter pour la vitesse
  float speed() const;
  void setSpeed(float speed);
};

#endif // BALL_H
