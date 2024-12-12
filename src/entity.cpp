#include "entity.hpp"
#include <allegro5/drawing.h>
#include <allegro5/allegro_primitives.h>

TestRectangle::TestRectangle(tpl position, float width, float height, ALLEGRO_COLOR color)
  :_position(position),
   _width(width),
   _height(height),
   _color(color) {}

TestRectangle::~TestRectangle() {}

void TestRectangle::draw() {
  const float x1 = _position.x - _width / 2;
  const float x2 = _position.x + _width / 2;
  const float y1 = _position.y - _height / 2;
  const float y2 = _position.y + _height / 2;
  al_draw_filled_rectangle(x1, y1, x2, y2, _color);
}

void TestRectangle::move(int dx, int dy) {
  _position.x += dx;
  _position.y += dy;
}
