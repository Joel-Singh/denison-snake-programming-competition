#include "lib/cells.h"
#include <string>

namespace writer {
/// \brief Create a string representation of cells that corresponds to \ref
/// reader::read_cells for use in calling a bot binary.
std::string write_cells(Cells const &cells);
} // namespace writer
