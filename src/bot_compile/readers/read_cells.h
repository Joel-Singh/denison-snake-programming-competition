#pragma once

#include "lib/cells.h"
#include <string>

/// \brief converts string to a \ref Cell. Throws if str is not a valid Cell
static Cell str_to_cell(std::string const &str);

namespace reader {
/// \brief Returns cells from a str. The str must begin with an integer
/// represent the row length, and then continue with each Cell from left to
/// right, top to bottom. Throws on malformed input
Cells read_cells(std::string str);

} // namespace reader
