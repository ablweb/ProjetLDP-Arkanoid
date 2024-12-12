#ifndef ENTITY_H
#define ENTITY_H

#include <allegro5/color.h>

struct tpl {
  float x=0, y=0;
};

class Entity {
protected:
  Entity() = default;
  Entity(const Entity&) = default;
public:
  virtual void draw() = 0;
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
  tpl _position;
  float _width;
  float _height;
  ALLEGRO_COLOR _color;
public:
  TestRectangle(tpl position, float width, float height, ALLEGRO_COLOR color);
  ~TestRectangle();
  void draw();
  void move(int dx, int dy);
};

#endif
