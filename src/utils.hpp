#ifndef UTILS_H
#define UTILS_H

#include <allegro5/color.h>

namespace RETURN_CODE {
enum {
  SUCCES,
  ENVIRONMENT_SETUP_FAIL
};
}; // namespace RETURN


namespace COLORS {
const ALLEGRO_COLOR BLACK = al_map_rgb(0, 0, 0);
const ALLEGRO_COLOR WHITE = al_map_rgb(255, 255, 255);
const ALLEGRO_COLOR RED = al_map_rgb(255, 0, 0);
const ALLEGRO_COLOR GREY = al_map_rgb(200, 200, 200);
const ALLEGRO_COLOR GREEN = al_map_rgb(0, 255, 0);
const ALLEGRO_COLOR YELLOW = al_map_rgb(255, 255, 0);
const ALLEGRO_COLOR PINK = al_map_rgb(200, 150, 167);
const ALLEGRO_COLOR MAGENTA = al_map_rgb(255, 0, 255);
const ALLEGRO_COLOR BLUE = al_map_rgb(0, 0, 255);
};  // namespace COLORS

#endif
