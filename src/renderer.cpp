#include "renderer.hpp"

#include <allegro5/allegro_primitives.h>
#include <memory>

#include "entity.hpp"

Renderer::Renderer() {}

Renderer::~Renderer() {}

void Renderer::refresh() {
}

void Renderer::drawTestRect(std::shared_ptr<TestRectangle> testRect) {
  const float x1 = testRect->x() - testRect->width() / 2;
  const float x2 = testRect->x() + testRect->width() / 2;
  const float y1 = testRect->y() - testRect->height() / 2;
  const float y2 = testRect->y() + testRect->height() / 2;
  al_draw_filled_rectangle(x1, y1, x2, y2, testRect->color());
}
