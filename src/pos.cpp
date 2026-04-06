#include "pos.h"
#include "game_settings.h"
#include "stdexcept"
#include <iostream>

// Origin is bottom left.
Pos::Pos(int x, int y) : x(x), y(y) {};

bool Pos::operator==(const Pos &other) const {
  return other.x == x && other.y == y;
}

/// \brief Returns a position if it moved in the given direction. Note,
/// Pos::with_dir does NOT mutate the position this is called on.
Pos Pos::with_dir(const Direction dir) const {
  Pos retPos = Pos(x,y);
  if (dir == Direction::UP) {
    retPos.y = retPos.y + 1;
  } else if (dir == Direction::DOWN) {
    retPos.y = retPos.y - 1;
  } else if (dir == Direction::LEFT) {
    retPos.x = retPos.x - 1;
  } else if (dir == Direction::RIGHT) {
    retPos.x = retPos.x + 1;
  } else {
    throw std::logic_error("Missing branch for Direction");
  }
  while(retPos.x>=GRID_SIZE){
    retPos.x = retPos.x - GRID_SIZE;
  }
  while(retPos.x<0){
    retPos.x = retPos.x + GRID_SIZE;
  }
  while(retPos.y>=GRID_SIZE){
    retPos.y = retPos.y - GRID_SIZE;
  }
  while(retPos.y<0){
    retPos.y = retPos.y + GRID_SIZE;
  }
  return retPos;
}

std::ostream &operator<<(std::ostream &os, const Pos &pos) {
  os << "Pos(" << pos.x << "," << pos.y << ")";
  return os;
}
