#include "direction.h"

std::string dir_to_str(Direction dir) {
  if (dir == Direction::UP) {
    return "UP";
  } else if (dir == Direction::DOWN) {
    return "DOWN";
  } else if (dir == Direction::LEFT) {
    return "LEFT";
  } else {
    return "RIGHT";
  }
}
