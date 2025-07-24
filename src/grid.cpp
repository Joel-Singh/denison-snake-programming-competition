#include "grid.h"
#include "stdexcept"

Grid::Grid(bool is_player_one, const Cells &cells,
           const std::vector<Pos> &player_one_segments,
           const std::vector<Pos> &player_two_segments)
    : cells(cells), is_player_one(is_player_one),
      player_one_segments(player_one_segments),
      player_two_segments(player_two_segments) {};

// Is 0 indexed
Cell Grid::get(int x, int y) const {
  int height = get_height();
  int width = get_width();

  if (x >= width || x < 0 || y >= height || y < 0) {
    throw std::logic_error("Invalid x y when calling Grid::get");
  }

  return cells.get(x, y);
}

int Grid::get_height() const { return cells.height(); }

// Assume that there is atleast one row and that all rows are the same size
int Grid::get_width() const { return cells.width(); }

std::vector<Pos> Grid::find_fruits() const { return find(Cell::FRUIT); }

Pos Grid::find_self_head() const {
  if (is_player_one) {
    return find(Cell::PLAYER_ONE_HEAD).at(0);
  } else {
    return find(Cell::PLAYER_TWO_HEAD).at(0);
  }
}

Pos Grid::find_other_head() const {
  if (is_player_one) {
    return find(Cell::PLAYER_TWO_HEAD).at(0);
  } else {
    return find(Cell::PLAYER_ONE_HEAD).at(0);
  }
}

// Includes the head
std::vector<Pos> Grid::find_self_positions() const {
  if (is_player_one) {
    return player_one_segments;
  } else {
    return player_two_segments;
  }
}

// Includes the head
std::vector<Pos> Grid::find_other_positions() const {
  if (is_player_one) {
    return player_two_segments;
  } else {
    return player_one_segments;
  }
}

std::vector<Pos> Grid::find(Cell cell) const {
  std::vector<Pos> found = {};
  for (int y = 0; y < get_height(); y++) {
    for (int x = 0; x < get_width(); x++) {
      if (get(x, y) == cell) {
        found.push_back(Pos(x, y));
      }
    }
  }
  return found;
}
