#include "bot_compile/readers/read_cells.h"
#include "lib/cells.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

/// \brief converts string to a \ref Cell. Throws if str is not a valid Cell
static Cell str_to_cell(std::string const &str) {
  if (str == "EMPTY") {
    return Cell::EMPTY;

  } else if (str == "FRUIT") {
    return Cell::FRUIT;

  } else if (str == "PLAYER_ONE") {
    return Cell::PLAYER_ONE;

  } else if (str == "PLAYER_ONE_HEAD") {
    return Cell::PLAYER_ONE_HEAD;

  } else if (str == "PLAYER_TWO") {
    return Cell::PLAYER_TWO;

  } else if (str == "PLAYER_TWO_HEAD") {
    return Cell::PLAYER_TWO_HEAD;

  } else {
    throw std::invalid_argument("`" + str + "`" + " is not a valid Cell");
  }
}

namespace reader {
/// \brief Returns cells from a str. The str must begin with an integer
/// represent the row length, and then continue with each Cell from left to
/// right, top to bottom. Throws on malformed input
Cells read_cells(std::string str) {
  if (str.size() < 3) {
    throw std::invalid_argument("Cells string is less than length 3");
  }

  std::string row_length_str = "";

  int i = 0;
  for (; i < str.size(); i++) {
    if (str.at(i) == ' ') {
      break;
    }
    row_length_str += str.at(i);
  }

  int row_length_int;
  row_length_int = std::stoi(row_length_str);

  if (i == str.size()) {
    throw std::invalid_argument("No cells following row length");
  }

  std::vector<std::vector<Cell>> cells_vec;

  while (i != (str.size() - 1)) {
    cells_vec.push_back(std::vector<Cell>());

    // Append all cells to a row
    for (int j = 0; j < row_length_int; j++) {
      // Move forward from the space or last character
      i++;

      if (i == str.size()) {
        throw std::invalid_argument("Not enough cells for last row");
      }

      std::string next_cell = "";

      while (str.at(i) != ' ') {
        next_cell += str.at(i);

        bool no_next_character = i + 1 == str.size();
        if (no_next_character) {
          break;
        }

        i++;
      }

      cells_vec.back().push_back(str_to_cell(next_cell));
      next_cell = "";
    }
  }

  // Reverse because str was from top to bottom, and the first element of cells
  // should be the "bottom".
  std::reverse(cells_vec.begin(), cells_vec.end());
  return Cells(cells_vec);
}

} // namespace reader
