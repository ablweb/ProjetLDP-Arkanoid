#include "renderer.hpp"

#include <allegro5/allegro_primitives.h>

#include <tuple>

#include "config.hpp"
#include "entity.hpp"
#include "level.hpp"
#include "utils.hpp"

Renderer::Renderer(ConstLevelSPtr level) : lvl(level) {}

Renderer::~Renderer() {}

void Renderer::refresh() {
  al_clear_to_color(COLORS::GREY);
  drawBackground();
  // https://stackoverflow.com/questions/1198260/how-can-you-iterate-over-the-elements-of-an-stdtuple
  std::apply([this](const auto&... entity) { ((render(entity.get())), ...); },
             lvl->all());
  al_flip_display();
}

void Renderer::drawBackground() {
  al_draw_filled_rectangle(SIDE_MARGIN,TOP_MARGIN,
                           DISPLAY_WIDTH-SIDE_MARGIN,
                           DISPLAY_HEIGHT-TOP_MARGIN,
                           COLORS::BLACK);
}

void Renderer::render(BrickHolder* brickHold) {
  for (const auto& b : brickHold->getContainer()) {
    if (b!=nullptr) render(b);
  }
}

void Renderer::render(Brick* brick) {
  const float x1 = brick->x() - brick->width() / 2;
  const float x2 = brick->x() + brick->width() / 2;
  const float y1 = brick->y() - brick->height() / 2;
  const float y2 = brick->y() + brick->height() / 2;
  al_draw_filled_rectangle(x1, y1, x2, y2, brick->color());
  ALLEGRO_COLOR color = COLORS::GREY_B;float thickness = 1;float offset = 1;
  if (brick->getType() == BRICK_CONST::gold
    || brick->getType() == BRICK_CONST::silver) {
    color = COLORS::WHITE;thickness = 2;offset = 2;
  }
  al_draw_rectangle(x1+offset, y1+offset, x2, y2, color, thickness);
}
