/// \file grid.h
/// \brief File containing grid
///

#pragma once

#include "cell.h"
#include "cells.h"
#include "pos.h"
#include <iostream>
#include <optional>
#include <vector>

///
/// \brief Represents the grid of cells containing snakes and fruits. Grid is
/// used in the [think](@ref MyBot) function to create your bot
///
/// Also see the std library
/// [vector](https://en.cppreference.com/w/cpp/container/vector.html) that is
/// returned from multiple methods.
class Grid {
public:
  ///
  /// \cond INTERNAL
  /// Hide the constructor as students will never directly use the constructor
  /// themselves
  Grid(const Cells &cells, bool is_player_one);
  ///
  /// \endcond
  ///

  /// Will throw an error if x and y are invalid
  Cell get(int x, int y) const;

  int get_height() const;

  int get_width() const;

  // Get the location of all fruits
  std::vector<Pos> find_fruits() const;

  // Get the position of your head
  Pos find_self_head() const;

  // Get the positions of all your parts
  std::vector<Pos> find_self_positions() const;

  // Get the position of the other snake's head
  Pos find_other_head() const;

  // Get the positions of the other snake's parts
  std::vector<Pos> find_other_positions() const;

private:
  const Cells &cells;
  bool is_player_one;
  std::vector<Pos> find(Cell cell) const;
};
