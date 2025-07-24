#include "cells.h"
#include "cell.h"
#include "space.h"
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>

// Create Cells with size width and size height
Cells::Cells(unsigned int size) {
  cells = std::vector<std::vector<Cell>>();

  for (int y = 0; y < size; y++) {
    cells.push_back(std::vector<Cell>());
    for (int x = 0; x < size; x++) {
      cells.at(y).push_back(Cell::EMPTY);
    }
  }
}

unsigned int Cells::height() const {
  assert(cells.size() > 0);
  return cells.size();
}

unsigned int Cells::width() const {
  assert(cells.size() > 0);
  // Assumes the the width is the same in every row
  return cells.at(0).size();
}

// 0 indexed, the origin is bottom left
Cell Cells::get(unsigned int x, unsigned int y) const {
  if (x >= width() || x < 0 || y >= height() || y < 0) {
    throw std::logic_error("Invalid x y when calling Cells::get");
  }

  return cells.at(y).at(x);
}

Cell Cells::get(Pos pos) const { return get(pos.x, pos.y); }

void Cells::set(unsigned int x, unsigned int y, Cell cell) {
  if (x >= width() || x < 0 || y >= height() || y < 0) {
    throw std::logic_error("Invalid x y when calling Cells::set");
  }
  cells.at(y).at(x) = cell;
}

void Cells::set(Pos pos, Cell cell) { set(pos.x, pos.y, cell); }
