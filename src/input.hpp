#ifndef INPUT_H
#define INPUT_H

#include "level.hpp"

#include <allegro5/events.h>
#include <memory>

class InputHandler {
private:
public:
  InputHandler();  // Constructeur
  ~InputHandler(); // Destructeur 

// Gestion des événements utilisateur
void handle(ALLEGRO_EVENT& event,std::shared_ptr<LevelManager> level, bool& running);

};

#endif
