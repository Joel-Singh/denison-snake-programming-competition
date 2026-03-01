#pragma once

#include "cell.h"
#include "pos.h"
#include <vector>

/// \cond INTERNAL
/// \brief Cells represent the board containing fruit, player
/// segments, empty spots, etc  
///
/// The difference betwee \ref Cells and \ref Grid is that Grid
/// is exposed to the competitors and can not be mutated while Cells
/// is used internally and can be mutated.

class Cells {
private:
  std::vector<std::vector<Cell>> cells;

public:
  Cells(unsigned int size);

  unsigned int height() const;

  unsigned int width() const;

  // 0 indexed, the origin is bottom left
  Cell get(unsigned int x, unsigned int y) const;

  Cell get(Pos pos) const;

  void set(unsigned int x, unsigned int y, Cell cell);

  void set(Pos pos, Cell cell);
};
/// \endcond
