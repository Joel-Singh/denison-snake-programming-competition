#include "cells.cpp"

// Passed in segments must be within cell_size x cell_size
Cells create_from_segments(unsigned int cell_size, std::vector<Pos> one_segments, std::vector<Pos> two_segments) {
  Cells cells(cell_size);

  for (int i = 0; i < one_segments.size(); i++) {
    Cell cell_to_set = i == 0 ? Cell::PLAYER_ONE_HEAD : Cell::PLAYER_ONE;
    try {
      cells.set(one_segments[i], cell_to_set);
    } catch (std::logic_error) {
      throw std::logic_error("Passed in segments not within 10x10 cells to create_from_segments");
    }
  }

  for (int i = 0; i < two_segments.size(); i++) {
    Cell cell_to_set = i == 0 ? Cell::PLAYER_TWO_HEAD : Cell::PLAYER_TWO;
    try {
      cells.set(two_segments[i], cell_to_set);
    } catch (std::logic_error) {
      throw std::logic_error("Passed in segments not within 10x10 cells to create_from_segments");
    }
  }

  return cells;
}
