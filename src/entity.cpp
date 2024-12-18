#include "entity.hpp"
#include <allegro5/drawing.h>
#include <allegro5/allegro_primitives.h>

// Constructeur pour la classe TestRectangle
TestRectangle::TestRectangle(tpl position, float width, float height, ALLEGRO_COLOR color)
  :_position(position),
   w(width),
   h(height),
   _color(color) {}

// Destructeur de TestRectangle
TestRectangle::~TestRectangle() {}

// Getters
float TestRectangle::x() { return pos.x; };
float TestRectangle::y() { return pos.y; };
float TestRectangle::width() { return w; };
float TestRectangle::height() { return h; };
ALLEGRO_COLOR TestRectangle::color() { return col; };

// Méthode pour dessiner un rectangle
void TestRectangle::draw() {
  const float x1 = pos.x - w / 2;
  const float x2 = pos.x + w / 2;
  const float y1 = pos.y -h / 2;
  const float y2 = pos.y +h / 2;
  // Dessine le rectangle avec les parametres spécifiés
  al_draw_filled_rectangle(x1, y1, x2, y2, col);
}

// Méthode pour déplacer le rectangle 
void TestRectangle::move(int dx, int dy) {
  pos.x += dx;
  pos.y += dy;
}
