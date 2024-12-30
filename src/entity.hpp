#ifndef ENTITY_H
#define ENTITY_H

#include <allegro5/color.h>
#include <vector>

#include "utils.hpp"

// -------------------------------------------------------------------------
// Entity
// -------------------------------------------------------------------------
class Entity {
protected:
  Entity(tpl position);
  Entity(const Entity&) = default;
  tpl pos;
public:
  virtual ~Entity() = default;
  float x() const;
  float y() const;
  void move(float dx, float dy);
};

// -------------------------------------------------------------------------
// Brick
// -------------------------------------------------------------------------

class Brick : public Entity {
private:
  const float w = BRICK_CONST::width;
  const float h = BRICK_CONST::height;
  BRICK_CONST::colorType type;
  BRICK_CONST::bonusType bonus;
  ALLEGRO_COLOR col;
  int life;
public:
  Brick(tpl position,
        BRICK_CONST::colorType brickType,
        BRICK_CONST::bonusType bonus);
  ~Brick();
  float width() const;
  float height() const;
  BRICK_CONST::colorType getType() const;
  ALLEGRO_COLOR color() const;
};

class BrickHolder {
private:
  std::vector<Brick*> brickContainer;
  static constexpr int maxRow = 8;
  static constexpr int maxCol = 14;
public:
  BrickHolder();
  BrickHolder(std::vector<BRICK_CONST::Param> bricksData);
  ~BrickHolder();
  void addBrick(BRICK_CONST::Param brickData);
  std::vector<Brick*> getContainer() const;
};

#endif
