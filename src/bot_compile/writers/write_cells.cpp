#include "bot_compile/writers/write_cells.h"
#include "lib/cell_to_str.h"

namespace writer {
std::string write_cells(Cells const &cells) {
  std::string cells_str = "";
  cells_str += std::to_string(cells.width());

  for (int y = cells.height() - 1; y >= 0; y--) {
    for (int x = 0; x < cells.width(); x++) {
      cells_str += " " + cell_to_str(cells.get(x, y));
    }
  }

  return cells_str;
};

} // namespace writer
