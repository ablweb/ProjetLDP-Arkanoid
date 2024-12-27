#ifndef ENTITY_H
#define ENTITY_H

#include <allegro5/color.h>
#include "utils.hpp"

class Entity {
protected:
  Entity() = default;
  Entity(const Entity&) = default;
public:
  virtual ~Entity() = default;
};

class DynamiqueEntity : public Entity {
protected:
  DynamiqueEntity() = default;
  DynamiqueEntity(const DynamiqueEntity&) = default;
public:
  virtual void move(int dx, int dy) = 0;
  virtual ~DynamiqueEntity() = default;
};

class TestRectangle : virtual public DynamiqueEntity {
private:
  tpl pos;
  float w;
  float h;
  ALLEGRO_COLOR col;
public:
  float x();
  float y();
  float width();
  float height();
  ALLEGRO_COLOR color();

  TestRectangle(tpl position, float width, float height, ALLEGRO_COLOR color);
  ~TestRectangle();
  void move(int dx, int dy);
};

#endif
