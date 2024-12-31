#include "renderer.hpp"

#include <allegro5/allegro_primitives.h>
#include <memory>

#include "entity.hpp"

Renderer::Renderer() {}

Renderer::~Renderer() {}

void Renderer::refresh() {
}

void Renderer::drawTestRect(std::shared_ptr<TestRectangle> testRect) {
  const float x1 = testRect->x() - testRect->width() / 2;
  const float x2 = testRect->x() + testRect->width() / 2;
  const float y1 = testRect->y() - testRect->height() / 2;
  const float y2 = testRect->y() + testRect->height() / 2;
  al_draw_filled_rectangle(x1, y1, x2, y2, testRect->color());
}


void Renderer::renderGame(std::shared_ptr<TestRectangle> palette) {
  al_clear_to_color(al_map_rgb(0, 0, 0)); // Efface l'écran

  // Dessine la raquette
  drawTestRect(palette);

  al_flip_display(); // Met à jour l'affichage 
}

void Renderer::renderGame(const LevelManager& level) {
  al_clear_to_color(al_map_rgb(0, 0, 0)); // Efface l'écran (noir)

  // Dessine la raquette
  drawTestRect(level.getPalette());

  // Dessine les briques
  for (const auto& brick : level.getBricks()) {
    drawTestRect(brick);
  }

  // Dessine la balle
  drawTestRect(level.getBall());

  // Dessine le score
  drawScore(level.getScore());

  // Dessine les vies
  drawLives(level.getLives());

  al_flip_display(); // Met à jour l'écran
}

void Renderer::drawScore(int score) {
  ALLEGRO_FONT* font = al_create_builtin_font(); // Police intégrée Allegro
  if (!font) {
    throw std::runtime_error("Failed to load font for score rendering");
  }

  al_draw_textf(
    font, 
    al_map_rgb(255, 255, 255), // Couleur blanche
    10, 10,                    // Position : en haut à gauche
    0,                         // Alignement
    "Score : %d", score         // Texte affiché avec le score
  );

  al_destroy_font(font); // Détruire la police après utilisation
}
void Renderer::drawLives(int lives) {
  ALLEGRO_FONT* font = al_create_builtin_font();
  if (!font) {
    throw std::runtime_error("Failed to load font for lives rendering");
  }

  al_draw_textf(
    font, 
    al_map_rgb(255, 255, 255), // Couleur blanche
    10, 30,                    // Position : juste en dessous du score
    0,                         // Alignement
    "Lives: %d", lives          // Texte affiché avec le nombre de vies
  );

  al_destroy_font(font);
}
