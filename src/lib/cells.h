#pragma once

#include "cell.h"
#include "pos.h"
#include <vector>

/// \cond INTERNAL
class Cells {
private:
  std::vector<std::vector<Cell>>
      cells; ///< The first index of cells is considered the "bottom".

public:
  Cells(unsigned int size);
  Cells(std::vector<std::vector<Cell>> cells_vec);

  unsigned int height() const;

  unsigned int width() const;

  // 0 indexed, the origin is bottom left
  Cell get(unsigned int x, unsigned int y) const;

  Cell get(Pos pos) const;

  void set(unsigned int x, unsigned int y, Cell cell);

  void set(Pos pos, Cell cell);
};
/// \endcond
