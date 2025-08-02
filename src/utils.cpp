#include "utils.hpp"

char bonusToChar(BRICK_CONST::bonusType bonus) {
  switch(bonus) {
    case BRICK_CONST::laser:        return 'L';
    case BRICK_CONST::bigger:       return 'B';
    case BRICK_CONST::capture:      return 'C';
    case BRICK_CONST::slow:         return 'S';
    case BRICK_CONST::interruption: return 'I';
    case BRICK_CONST::player:       return 'P';
    default:                        return '?';
  }
}