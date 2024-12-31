#include "ball.hpp"
#include <cmath> // Pour std::sqrt

// Constructeur
Ball::Ball(tpl position, float width, float height, ALLEGRO_COLOR color, float speed)
  : TestRectangle(position, width, height, color), _dx(1.0f), _dy(-1.0f), _speed(speed) {}

// Déplace la balle
void Ball::move() {
  _position.x += _dx * _speed;
  _position.y += _dy * _speed;
}

// Rebonds
void Ball::bounceHorizontal() {
  _dx = -_dx;
}

void Ball::bounceVertical() {
  _dy = -_dy;
}

// Change la direction
void Ball::setDirection(float dx, float dy) {
  _dx = dx;
  _dy = dy;

  // Normalise la direction pour conserver une vitesse constante
  float length = std::sqrt(_dx * _dx + _dy * _dy);
  if (length != 0) {
    _dx /= length;
    _dy /= length;
  }
}

// Getters pour la direction
float Ball::dx() const {
  return _dx;
}

float Ball::dy() const {
  return _dy;
}

// Getter et setter pour la vitesse
float Ball::speed() const {
  return _speed;
}

void Ball::setSpeed(float speed) {
  _speed = speed;
}
