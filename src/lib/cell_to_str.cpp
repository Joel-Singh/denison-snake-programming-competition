#include "lib/cell_to_str.h"

std::string cell_to_str(Cell cell) {
  if (cell == Cell::EMPTY) {
    return "EMPTY";
  } else if (cell == Cell::FRUIT) {
    return "FRUIT";
  } else if (cell == Cell::PLAYER_ONE) {
    return "PLAYER_ONE";
  } else if (cell == Cell::PLAYER_ONE_HEAD) {
    return "PLAYER_ONE_HEAD";
  } else if (cell == Cell::PLAYER_TWO) {
    return "PLAYER_TWO";
  } else {
    return "PLAYER_TWO_HEAD";
  }
}
