/// \file grid.h
/// \brief File containing grid
///

#pragma once

#include "cell.h"
#include "lib/cells.h"
#include "pos.h"
#include <iostream>
#include <optional>
#include <vector>

///
/// \brief Represents the grid of cells containing snakes and fruits. Grid is
/// used in the \ref MyBot::think function to create your bot
///
/// Also see the std library
/// [vector](https://en.cppreference.com/w/cpp/container/vector.html) that is
/// returned from multiple methods. You can think of a vector as analagous to a
/// python list.
class Grid {
public:
  ///
  /// \cond INTERNAL
  /// Hide the constructor as students will never directly use the constructor
  /// themselves
  ///
  /// \param player_one_segments,player_two_segments the ordered segments of
  /// each snake with the first element being the head.
  Grid(bool is_player_one, const int current_tick, const Cells &cells,
       const std::vector<Pos> &player_one_segments,
       const std::vector<Pos> &player_two_segments);
  ///
  /// \endcond
  ///

  /// \brief Returns a \ref Cell at (x, y) or throws if x and y are invalid
  ///
  /// x is valid inclusively from 0 to Grid::get_height() -1 and y
  /// is valid inclusively from 0 to Grid::get_width() -1.
  Cell get(int x, int y) const;

  /// \brief Returns a \ref Cell at `pos` or throws if pos is invalid
  ///
  /// A valid `pos` has an x-component inclusively from 0 to Grid::get_height()
  /// -1 and has y-component from 0 to Grid::get_width() -1.
  Cell get(Pos pos) const;

  /// \brief Returns the height of the grid.
  int get_height() const;

  /// \brief Returns the width of the grid.
  int get_width() const;

  /// \brief Returns the current tick with 0 being the first tick and \ref
  /// FINAL_TICK being the last. If get_current_tick() == \ref FINAL_TICK, then
  /// the game will finish at the end of this tick.
  int get_current_tick() const;

  /// \brief Returns all fruit as a std::vector<@ref Pos>
  std::vector<Pos> find_fruits() const;

  /// \brief Get the position of your head
  Pos find_self_head() const;

  /// \brief Get the ordered positions of all your parts. The first element is
  /// the head.
  std::vector<Pos> find_self_positions() const;

  /// \brief Returns the head of the other snake.
  Pos find_other_head() const;

  /// \brief Get the ordered positions of the other snake. The first element is
  /// their head.
  std::vector<Pos> find_other_positions() const;

private:
  const Cells &cells;
  bool is_player_one;
  const int current_tick;
  const std::vector<Pos> &player_one_segments;
  const std::vector<Pos> &player_two_segments;
  std::vector<Pos> find(Cell cell) const;
};
