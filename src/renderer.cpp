#include "renderer.hpp"

#include <allegro5/allegro_primitives.h>

#include <iostream>
#include <tuple>

#include "entity.hpp"
#include "level.hpp"

Renderer::Renderer(ConstLevelSPtr level) : lvl(level) {}

Renderer::~Renderer() {}

void Renderer::refresh() {
  // https://stackoverflow.com/questions/1198260/how-can-you-iterate-over-the-elements-of-an-stdtuple
  std::apply([this](const auto&... entity) { ((render(entity.get())), ...); },
             lvl->all());
}

void Renderer::renderType(Entity* entity) {
  if (auto testRect = dynamic_cast<TestRectangle*>(entity)) {
    std::cerr << "|Renderer::renderType() -> TestRectangle\n";
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
