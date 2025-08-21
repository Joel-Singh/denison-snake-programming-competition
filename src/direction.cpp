#include "direction.h"
#include <stdexcept>

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

Direction str_to_dir(string str) {
  if (str == "UP") {
    return Direction::UP;
  } else if (str == "DOWN") {
    return Direction::DOWN;
  } else if (str == "LEFT") {
    return Direction::LEFT;
  } else if (str == "RIGHT") {
    return Direction::RIGHT;
  } else {
    throw invalid_argument("`" + str + "`" + " is not a valid direction");
  }
}
