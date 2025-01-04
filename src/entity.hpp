#ifndef ENTITY_H
#define ENTITY_H

#include <allegro5/color.h>
#include <vector>

#include "utils.hpp"

// -------------------------------------------------------------------------
// Entity
// -------------------------------------------------------------------------
class CollisionRect;
class CollisionCircle;
class Entity {
protected:
  Entity(tpl position);
  Entity(const Entity&) = default;
  tpl _pos;
public:
  virtual ~Entity() = default;
  float x() const;
  float y() const;
};

// -------------------------------------------------------------------------
// DynamiqueEntity
// -------------------------------------------------------------------------
class DynamiqueEntity : public Entity {
protected:
  DynamiqueEntity(tpl position);
  DynamiqueEntity(const DynamiqueEntity&) = default;
public:
  virtual ~DynamiqueEntity() = default;
  virtual void move(float dx, float dy);
};

// -------------------------------------------------------------------------
// CollisionRect
// -------------------------------------------------------------------------
class CollisionCircle;
class CollisionRect {
private:
  tpl   * _c_pos;
  float * _c_w;
  float * _c_h;
public:
  CollisionRect(tpl* position, float* width, float* height);
  ~CollisionRect();

  float colX() const;
  float colY() const;
  float colWidth() const;
  float colHeight() const;

  tpl colPoint = {0,0};
  bool checkCollision(const CollisionRect* other);
  bool checkCollision(const CollisionCircle* other);
  virtual void collisionDetected(Entity*,tpl) = 0;
};

// -------------------------------------------------------------------------
// CollisionCircle
// -------------------------------------------------------------------------
class CollisionCircle {
private:
  tpl   * _c_pos;
  float * _c_rad;
public:
  CollisionCircle(tpl* position, float* radius);
  ~CollisionCircle();

  float colX() const;
  float colY() const;
  float colRadius() const;
  
  tpl colPoint = {0,0};
  bool checkCollision(const CollisionRect* other);
  virtual void collisionDetected(Entity*,tpl) = 0;
};

// -------------------------------------------------------------------------
// Brick
// -------------------------------------------------------------------------
class BrickHolder;
class Brick : public Entity, public CollisionRect {
private:
  float _w = BRICK_CONST::width;
  float _h = BRICK_CONST::height;
  BRICK_CONST::colorType _type;
  BRICK_CONST::bonusType _bonus;
  ALLEGRO_COLOR _col;
  int _life;

  BrickHolder* _holder;
  void destroy();
public:
  Brick(tpl position,
        BRICK_CONST::colorType brickType,
        BRICK_CONST::bonusType bonus,
        BrickHolder* holder);
  ~Brick();

  float width() const;
  float height() const;
  BRICK_CONST::colorType getType() const;
  ALLEGRO_COLOR color() const;

  void collisionDetected(Entity*,tpl) override;
};

// -------------------------------------------------------------------------
// BrickHolder
// -------------------------------------------------------------------------
class BrickHolder {
private:
  std::vector<Brick*> brickContainer;
  static constexpr int maxRow = 8;
  static constexpr int maxCol = 14;
public:
  BrickHolder();
  BrickHolder(std::vector<BRICK_CONST::Param> bricksData);
  ~BrickHolder();

  std::vector<Brick*> getContainer() const;

  void addBrick(BRICK_CONST::Param brickData);
  void removeBrick(Brick* brick);
};

// -------------------------------------------------------------------------
// Paddle
// -------------------------------------------------------------------------
class Paddle : public DynamiqueEntity, public CollisionRect {
 private:
  float _w,_h,_spd;
  ALLEGRO_COLOR _col;
  void move(float dx, float dy) override;
 public:
  Paddle(tpl position, ALLEGRO_COLOR color);
  ~Paddle();

  float width() const;
  float height() const;
  ALLEGRO_COLOR color() const;

  void move(bool direction);
  void collisionDetected(Entity*,tpl) override;
};

// -------------------------------------------------------------------------
// Ball
// -------------------------------------------------------------------------
class Ball : public DynamiqueEntity, public CollisionCircle {
 private:
  float _dx,_dy,_spd,_rad;
  ALLEGRO_COLOR _col;
  void move(float dx, float dy) override;
  void bounceHorizontal();
  void bounceVertical();
  void setDirection(float dx, float dy);
  void handleCollision(Brick* brick, tpl collisionPoint);
  void handleCollision(Paddle* paddle, tpl collisionPoint);
 public:
  Ball(tpl position, float speed, float radius, ALLEGRO_COLOR color);
  ~Ball();

  bool isAttached;
  float radius() const;
  ALLEGRO_COLOR color() const;

  void go();
  void setPos(float x);
  void move();
  void collisionDetected(Entity*,tpl) override;
};

#endif
