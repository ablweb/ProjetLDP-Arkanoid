#include "entity.hpp"
#include <allegro5/drawing.h>
#include <allegro5/allegro_primitives.h>

TestRectangle::TestRectangle(tpl position, float width, float height, ALLEGRO_COLOR color)
  :_position(position),
   _width(width),
   _height(height),
   _color(color) {}

TestRectangle::~TestRectangle() {}

float TestRectangle::x() { return pos.x; };
float TestRectangle::y() { return pos.y; };

float TestRectangle::width() { return w; };
float TestRectangle::height() { return h; };

ALLEGRO_COLOR TestRectangle::color() { return col; };

void TestRectangle::draw() {
  const float x1 = _position.x - _width / 2;
  const float x2 = _position.x + _width / 2;
  const float y1 = _position.y - _height / 2;
  const float y2 = _position.y + _height / 2;
  al_draw_filled_rectangle(x1, y1, x2, y2, _color);
}

// Méthode pour déplacer le rectangle
void TestRectangle::move(int dx, int dy) {
  _position.x += dx;
  _position.y += dy;
}
