#pragma once

#include "direction.h"
#include "stdexcept"
#include <iostream>

/// \brief @ref Pos represents a position on the @ref Grid; the origin is bottom
/// left.
class Pos {
public:
  int x;
  int y;
  Pos(int x, int y);
  bool operator==(const Pos &other) const;
  Pos with_dir(const Direction dir) const;
};

std::ostream &operator<<(std::ostream &os, const Pos &pos);
