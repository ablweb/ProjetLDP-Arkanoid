#ifndef RENDERER_H
#define RENDERER_H

#include <memory>

class TestRectangle;

class Renderer {
private:
public:
  void drawTestRect(std::shared_ptr<TestRectangle> testRect);
  Renderer();
  ~Renderer();
  void refresh();
};

#endif
