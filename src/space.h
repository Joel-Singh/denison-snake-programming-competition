#pragma once

#include "stdexcept"
#include <iostream>

enum Direction { UP, DOWN, LEFT, RIGHT };

// Origin is bottom left.
class Pos {
public:
  int x;
  int y;
  Pos(int x, int y);
  bool operator==(const Pos &other) const;
  Pos with_dir(const Direction dir) const;
};

std::ostream &operator<<(std::ostream &os, const Pos &pos);
