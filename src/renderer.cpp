#include "renderer.hpp"

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "config.hpp"
#include "entity.hpp"
#include "env.hpp"
#include "level.hpp"
#include "utils.hpp"

Renderer::Renderer(ConstLevelSPtr level) : lvl(level) {}

Renderer::~Renderer() {}

void Renderer::saveScore(int c) { _savedScore = c; }

void Renderer::refresh() {
  al_clear_to_color(COLORS::GREY);
  drawBackground();
  if (GAME_STATE==IN_GAME) {
    drawGameInfo();
    for (Entity* entity : lvl->all()) {
      render(entity);
    }
  }
  else if (GAME_STATE==VICTORY) {
    drawVictoryMessage();
  }
  else if (GAME_STATE==LOSE) {
    drawLoseMessage();
  }
  al_flip_display();
}

void Renderer::drawVictoryMessage() {
  drawGameInfo();
  al_draw_textf(env.FONT_HUGE,COLORS::GREEN,
                (float)DISPLAY_WIDTH/2,
                (float)DISPLAY_HEIGHT/2,
                ALLEGRO_ALIGN_CENTER,
                "Victory!");
  al_draw_text(env.FONT_HUGE,COLORS::WHITE,
                (float)DISPLAY_WIDTH/2,
                (float)DISPLAY_HEIGHT/2+FONT_SIZE*2,
                ALLEGRO_ALIGN_CENTER,
               "Press any key to continue");
}
void Renderer::drawLoseMessage() {
  al_draw_textf(env.FONT_HUGE,COLORS::GREEN,
                (float)DISPLAY_WIDTH/2,
                (float)DISPLAY_HEIGHT/2,
                ALLEGRO_ALIGN_CENTER,
                "GAME OVER... Your Final Score: %d", _savedScore);
  al_draw_text(env.FONT_HUGE,COLORS::WHITE,
               (float)DISPLAY_WIDTH/2,
               (float)DISPLAY_HEIGHT/2+FONT_SIZE*2,
               ALLEGRO_ALIGN_CENTER,
               "Press any key to restart");
}
void Renderer::drawBackground() {
  al_draw_filled_rectangle(SIDE_MARGIN,TOP_MARGIN,
                           DISPLAY_WIDTH-SIDE_MARGIN,
                           DISPLAY_HEIGHT-TOP_MARGIN,
                           COLORS::BLACK);
  al_draw_rectangle(12,12,DISPLAY_WIDTH-12,DISPLAY_HEIGHT-12,
                    COLORS::GREY_B,24);
}
void Renderer::drawGameInfo() {
  drawScore();
  drawLevelName();
  drawRemainingLives();
  drawKeyInfo();
} 
void Renderer::drawScore() {
  float offset = 10;
  al_draw_textf(env.FONT_HUGE, COLORS::YELLOW,
                SIDE_MARGIN+offset, TOP_MARGIN,
                0,"%i", lvl->getScore());
}
void Renderer::drawLevelName() {
  al_draw_text(env.FONT_HUGE, COLORS::FONT_C,
               (float)DISPLAY_WIDTH/2, (TOP_MARGIN/2)-((float)FONT_SIZE/2),
               1, lvl->levelName.c_str());
}
void Renderer::drawRemainingLives() {
  float rectWidth = 30.0f;
  float rectHeight = 10.0f;
  float offsetH = 20;
  float offsetV = 15;
  for (int i=1;i<=lvl->getLives();i++) {
    float x1 = DISPLAY_WIDTH-SIDE_MARGIN-offsetH - rectWidth/2;
    float x2 = (DISPLAY_WIDTH-SIDE_MARGIN-offsetH + rectWidth/2)-3;
    float y1 = TOP_MARGIN+offsetV - rectHeight/2;
    float y2 = TOP_MARGIN+offsetV + rectHeight/2;
    al_draw_filled_rectangle(x1,y1,x2,y2,COLORS::GREEN);
    offsetH+=rectWidth;
  }
}
void Renderer::drawKeyInfo() {
  float offset = 5;
  al_draw_multiline_text(env.FONT, COLORS::FONT_C,
                         SIDE_MARGIN+offset,
                         DISPLAY_HEIGHT-TOP_MARGIN+offset,
                         DISPLAY_WIDTH-SIDE_MARGIN-offset, 15,
                         0,HELP::DISPLAY_KEY_INFO.c_str());
}

// -------------------------------------------------------------------------
// Entities
// -------------------------------------------------------------------------
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

  // Affichage de la lettre bonus si elle existe
  if (brick->hasBonus()) {
  char letter = bonusToChar(brick->getBonus());

    ALLEGRO_FONT* font = al_create_builtin_font(); // Police simple intégrée
    al_draw_textf(font,COLORS::BLACK,brick->x(), brick->y() - 5, ALLEGRO_ALIGN_CENTER,"%c", letter);
    al_destroy_font(font); // Libération mémoire
  }
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
