#include "renderer.hpp"

#include <allegro5/allegro_primitives.h>

#include "entity.hpp"

Renderer::Renderer() {}

Renderer::~Renderer() {}

void Renderer::refresh() {
}

void Renderer::onNotify(Entity* entity) {
  renderType(entity);
}

void Renderer::renderType(Entity* entity) {
  if (auto* testRect = dynamic_cast<TestRectangle*>(entity)) {
    render(testRect);
  }
}

void Renderer::render(TestRectangle* testRect) {
  const float x1 = testRect->x() - testRect->width() / 2;
  const float x2 = testRect->x() + testRect->width() / 2;
  const float y1 = testRect->y() - testRect->height() / 2;
  const float y2 = testRect->y() + testRect->height() / 2;
  al_draw_filled_rectangle(x1, y1, x2, y2, testRect->color());
}
