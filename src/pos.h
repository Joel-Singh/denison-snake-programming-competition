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

  /// \brief Helper method to give the position if it went in a certain
  /// direction.
  ///
  /// For example:
  /// ```
  /// Pos my_pos(3, 4);
  /// Direction up = Direction::UP;
  ///
  /// // Will print "Pos(3, 5)"
  /// std::cout << my_pos.with_dir(up) << std::endl;
  /// ```
  Pos with_dir(const Direction dir) const;
};

std::ostream &operator<<(std::ostream &os, const Pos &pos);
