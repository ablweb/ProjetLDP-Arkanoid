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
void updateWidthPointer(float* newWidth);  
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
  void fixOverlap(DynamiqueEntity* thisEntity);
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
  int _lives;
  int& _scoreRef;

  BrickHolder* _holder;
  void destroy();
public:
  Brick(tpl position,
        BRICK_CONST::colorType brickType,
        BRICK_CONST::bonusType bonus,
        BrickHolder* holder,
        int& score);
  ~Brick();

  float width() const;
  float height() const;
  BRICK_CONST::colorType getType() const;
  BRICK_CONST::bonusType getBonus() const;

  ALLEGRO_COLOR color() const;
  bool isDestructable() const;
  bool hasBonus() const;

  void collisionDetected(Entity*,tpl) override;
};

// -------------------------------------------------------------------------
// BrickHolder
// -------------------------------------------------------------------------
class Level; 

class BrickHolder {
private:
  std::vector<Brick*> brickContainer;
  static constexpr int maxRow = 8;
  static constexpr int maxCol = 14;
  Level* _level;
  int& _score;
public:
  BrickHolder(Level* level,int& score);
  Level* getLevel() const { return _level; } 

  BrickHolder(Level* level, int& score, std::vector<BRICK_CONST::Param> bricksData);
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
  void widen(float factor = 1.5f);
  void collisionDetected(Entity*,tpl) override;
  void resetWidth();

};

// -------------------------------------------------------------------------
// Ball
// -------------------------------------------------------------------------
class Ball : public DynamiqueEntity, public CollisionCircle {
 private:
  float _dx,_dy,_spd,_rad;
  ALLEGRO_COLOR _col;
  uint _bounceCount;
  int& _livesRef;
  void move(float dx, float dy) override;
  void resetBall();
  void bounceHorizontal();
  void bounceVertical();
  void updateSpeed();
  void setDirection(float dx, float dy);
 public:
  Ball(tpl position, float speed, float radius, ALLEGRO_COLOR color, int& lives);
  ~Ball();

  bool isAttached;
  float radius() const;
  ALLEGRO_COLOR color() const;

  void go();
  void setPos(float x);
  void move();
  float getSpeed() const;
  void setSpeed(float speed);

  void collisionDetected(Entity*,tpl) override;
 private:
  void handleCollision(Brick* brick, tpl collisionPoint);
  void handleCollision(Paddle* paddle, tpl collisionPoint);
};

// -------------------------------------------------------------------------
// Bonus
// -------------------------------------------------------------------------

class Bonus :  public DynamiqueEntity, public CollisionCircle {
 private:
  float _velocityY;
  float _radius = 10.0f;
  char _letter;
  bool _active;
  ALLEGRO_COLOR _color;
  

  float groundLevel() const;
  void onGroundCollision();
 public:
  Bonus(float x, float y, char letter, ALLEGRO_COLOR color);
  ~Bonus();

  void activate();                    // Lancer la descente
  void update(float deltaTime);      // Mettre à jour la position
  void render() const;               // Dessiner le bonus
  void collisionDetected(Entity*, tpl) override; // Gérer la collision avec paddle
  void deactivate(); // dans la déclaration

  char getLetter() const;            // pour afficher la lettre
  bool isActive() const;             //  savoir s’il est actif
  tpl position() const { return _pos; } // Accès à la position
};
#endif
