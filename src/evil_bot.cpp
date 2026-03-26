#include "evil_bot.h"
#include "grid.h"
#include "pos.h"
#include <stdexcept>
#include <string>
#include <pybind11/embed.h>

#include "lib/writers/write_cells.h"
#include "lib/writers/write_segments.h"

namespace py = pybind11;

/// \brief This evil bot goes to the closest fruit on the board if one exists,
/// else, just go in a random direction
///
/// There are a couple of flaws with this bot. Firstly, EvilBot doesn't check to
/// see if the direction they're going in is safe (i.e isn't a segment or wall.)
/// Secondly, EvilBot never moves towards fruit diagonally, only cardinally. And
/// many more. This initial code is meant to give an example of how to use \ref
/// Grid and write a bot.
Direction EvilBot::think(const Grid &grid) const {
  py::scoped_interpreter guard{}; // start the interpreter and keep it alive

  py::module_ evil_bot = py::module::import("src.python.evil_bot_wrapper");

  std::string is_player_one_str = grid.is_player_one ? "true" : "false";
  std::string current_tick_str = std::to_string(grid.current_tick);
  std::string cells_str = write_cells(grid.cells);
  std::string player_one_segments_str = write_segments(grid.player_one_segments);
  std::string player_two_segments_str = write_segments(grid.player_two_segments);
  py::object result = evil_bot.attr("think_wrapper")(is_player_one_str + "\n" + current_tick_str + "\n" + cells_str + "\n" + player_one_segments_str + "\n" + player_two_segments_str);

  std::string direction = result.cast<std::string>();
  if (direction == "UP") {
    return Direction::UP;
  } else if (direction == "DOWN") {
    return Direction::DOWN;
  } else if (direction == "LEFT") {
    return Direction::LEFT;
  } else if (direction == "RIGHT") {
    return Direction::RIGHT;
  } else {
    throw std::logic_error("Missing branch");
  }
}
