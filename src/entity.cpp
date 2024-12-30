#include "entity.hpp"

#include <allegro5/allegro_primitives.h>
#include <allegro5/drawing.h>

#include "config.hpp"
#include "utils.hpp"

// -------------------------------------------------------------------------
// Entity
// -------------------------------------------------------------------------
Entity::Entity(tpl position) : pos(position) {}
float Entity::x() const { return pos.x; }
float Entity::y() const { return pos.y; }
void Entity::move(float dx, float dy) {pos.x += dx;pos.y += dy;}

// -------------------------------------------------------------------------
// Brick
// -------------------------------------------------------------------------
Brick::Brick(tpl position,
             BRICK_CONST::colorType brickType,
             BRICK_CONST::bonusType bonusType)
  : Entity(position), type(brickType), bonus(bonusType) {
  col = BRICK_CONST::typeToColor.at(type);
  switch (brickType) {
    case BRICK_CONST::silver:
      life = 2;
      break;
    case BRICK_CONST::gold:
      life = -1;
      break;
    default: life = 1;
      break;
  }
}
Brick::~Brick() {}

float Brick::width() const { return w; }
float Brick::height() const { return h; }
BRICK_CONST::colorType Brick::getType() const { return type; }
ALLEGRO_COLOR Brick::color() const { return col; }

// -------------------------------------------------------------------------
// BrickHolder
// -------------------------------------------------------------------------
BrickHolder::BrickHolder(std::vector<BRICK_CONST::Param> bricksData){
  for (const auto& b:bricksData) {
    addBrick(b);
  }
}
BrickHolder::BrickHolder() {}
BrickHolder::~BrickHolder() {
  for (auto brick : brickContainer) {
    delete brick;
  }
  brickContainer.clear(); 
}

void BrickHolder::addBrick(BRICK_CONST::Param b) {
  if (b.row >= maxRow || b.col >= maxCol) {
    throw std::out_of_range("Brick position out of grid bounds");
  }
  using namespace BRICK_CONST;
  brickContainer.push_back(new Brick(
    tpl{((float)b.col+1) * (width + spacing) + BRICK_SIDE_MARGIN,
        ((float)b.row+1) * (height + spacing) + BRICK_TOP_MARGIN},
    b.color,
    b.bonus));
}
std::vector<Brick*> BrickHolder::getContainer() const {
  return brickContainer;
}
