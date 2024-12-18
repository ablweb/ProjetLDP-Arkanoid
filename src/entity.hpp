#ifndef ENTITY_H
#define ENTITY_H

#include <allegro5/color.h>

struct tpl {
  float x=0, y=0;
};
// Classe abstraite de base pour toutes les entités
class Entity {
protected:
  Entity() = default;
  Entity(const Entity&) = default;
public:
  virtual void draw() = 0;    // Méthode pour dessiner l'entité
  virtual void update() = 0;    // Méthode à redéfinir pour les entités dynamiques
  virtual ~Entity() = default; // Destructeur virtuel pour la gestion des entités dérivées
};

// Classe abstraite pour les entités dynamiques (qui peuvent se déplacer)
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
  tpl pos; // Position du rectangle
  float w;  // width du rectangle
  float h;  // Height du rectangle
  ALLEGRO_COLOR col; // Couleur du rectangle
public:
  float x();
  float y();
  float width();
  float height();
  ALLEGRO_COLOR color();

  TestRectangle(tpl position, float width, float height, ALLEGRO_COLOR color);
  ~TestRectangle();
  void draw();
  void move(int dx, int dy);
};

#endif
