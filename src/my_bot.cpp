#include "my_bot.h"
#include "grid.h"
#include "pos.h"
#include <string>
#include <pybind11/embed.h>

#include "lib/writers/write_cells.h"
#include "lib/writers/write_segments.h"

namespace py = pybind11;

/// \brief The function you'll implement for your bot! The default code here
/// simply has `MyBot` move randomly, only going into squares that are empty or
/// have fruit.
Direction MyBot::think(const Grid &grid) const {
  py::scoped_interpreter guard{}; // start the interpreter and keep it alive

  py::module_ my_bot = py::module::import("src.python.my_bot_wrapper");

  std::string is_player_one_str = grid.is_player_one ? "true" : "false";
  std::string current_tick_str = std::to_string(grid.current_tick);
  std::string cells_str = write_cells(grid.cells);
  std::string player_one_segments_str = write_segments(grid.player_one_segments);
  std::string player_two_segments_str = write_segments(grid.player_two_segments);
  py::object result = my_bot.attr("think_wrapper")(is_player_one_str + "\n" + current_tick_str + "\n" + cells_str + "\n" + player_one_segments_str + "\n" + player_two_segments_str);

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
