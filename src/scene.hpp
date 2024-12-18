#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>
#include <algorithm> // pour std::remove_if


class Entity;

class Scene {
private:
  std::vector<std::shared_ptr<Entity>> entities;
public:
  // Constructeur
  Scene() = default;

  // Destructeur
  ~Scene() = default;

  // Ajouter une entité à la scène
  void addEntity(std::shared_ptr<Entity> entity);

  // Supprimer une entité de la scène
  void removeEntity(std::shared_ptr<Entity> entity);

  // Mettre à jour toutes les entités ( pour les déplacements)
  void update();

  // Dessiner toutes les entités
  void draw();
};

#endif
