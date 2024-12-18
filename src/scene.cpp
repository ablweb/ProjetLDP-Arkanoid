#include "scene.hpp"
#include "entity.hpp"  

// Constructeur par défaut
Scene::Scene() = default;

// Destructeur par défaut
Scene::~Scene() = default;

// Ajouter une entité à la scène
void Scene::addEntity(std::shared_ptr<Entity> entity) {
    entities.push_back(entity);
}

// Supprimer une entité de la scène
void Scene::removeEntity(std::shared_ptr<Entity> entity) {
    entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
}

// Mettre à jour toutes les entités (appeler une méthode update sur chaque entité)
void Scene::update() {
    for (auto& entity : entities) {
        entity->update();  
    }
}

// Dessiner toutes les entités (appeler une méthode draw sur chaque entité)
void Scene::draw() {
    for (auto& entity : entities) {
        entity->draw();  
    }
}
