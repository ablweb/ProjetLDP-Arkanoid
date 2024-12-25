#ifndef RENDERER_H
#define RENDERER_H

#include "utils.hpp"
#include "entity.hpp"

class TestRectangle;

class Renderer : public Listener<Entity> {
private:
  void onNotify(Entity*) override;
public:
  Renderer();
  ~Renderer();
  void refresh();

  void renderType(Entity*);
  void render(TestRectangle*);
  // add new render methodes with other parameters
};

#endif
