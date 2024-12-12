#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>

class Entity;

class Scene {
private:
  std::vector<std::shared_ptr<Entity>> entities;
public:
  Scene();
  ~Scene();
};

#endif
