#include "renderer.hpp"

#include <allegro5/allegro_primitives.h>

#include "config.hpp"
#include "entity.hpp"
#include "level.hpp"
#include "utils.hpp"

Renderer::Renderer(ConstLevelSPtr level) : lvl(level) {}

Renderer::~Renderer() {}

void Renderer::refresh() {
  al_clear_to_color(COLORS::GREY);
  drawBackground();
  for (Entity* entity : lvl->all()) {
    render(entity);
  }
  al_flip_display();
}

void Renderer::drawBackground() {
  al_draw_filled_rectangle(SIDE_MARGIN,TOP_MARGIN,
                           DISPLAY_WIDTH-SIDE_MARGIN,
                           DISPLAY_HEIGHT-TOP_MARGIN,
                           COLORS::BLACK);
  al_draw_rectangle(12,12,DISPLAY_WIDTH-12,DISPLAY_HEIGHT-12,
                    COLORS::GREY_B,24);
}

void Renderer::render(Entity* entity) {
  if (auto ball = dynamic_cast<Ball*>(entity)) {
    render(ball);
  } else if (auto paddle = dynamic_cast<Paddle*>(entity)) {
    render(paddle);
  } else if (auto brick = dynamic_cast<Brick*>(entity)) {
    render(brick);
  } else if (auto brickHolder = dynamic_cast<BrickHolder*>(entity)) {
    render(brickHolder);
  }
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
  ALLEGRO_COLOR color = COLORS::GREY_B;float thickness = 1;float offset = 0;
  if (brick->getType() == BRICK_CONST::gold
    || brick->getType() == BRICK_CONST::silver) {
    color = COLORS::WHITE;thickness = 2;offset = 1;
  }
  al_draw_rectangle(x1+offset, y1+offset, x2-offset, y2-offset, color, thickness);
}

void Renderer::render(Paddle* paddle) {
  const float x1 = paddle->x() - paddle->width() / 2;
  const float x2 = paddle->x() + paddle->width() / 2;
  const float y1 = paddle->y() - paddle->height() / 2;
  const float y2 = paddle->y() + paddle->height() / 2;
  al_draw_filled_rectangle(x1, y1, x2, y2, paddle->color());
  al_draw_rectangle(x1+1, y1+1, x2, y2, COLORS::GREY_B, 1);
}

void Renderer::render(Ball* ball) {
  al_draw_filled_circle(ball->x(), ball->y(), ball->radius(), ball->color());
  al_draw_circle(ball->x(), ball->y(), ball->radius()-1, COLORS::GREEN, 2);
}
