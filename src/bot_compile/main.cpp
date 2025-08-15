#include "bot_compile/compile_bot.h"
#include "bot_compile/readers/current_tick.h"
#include "bot_compile/readers/is_player_one.h"
#include "bot_compile/readers/read_cells.h"
#include "bot_compile/readers/read_player_segments.h"
#include "direction.h"
#include "game_settings.h"
#include "lib/cells.h"
#include "lib/create_from_segments.h"
#include "pos.h"
#include <vector>

/// \brief Takes in the current state of the board arguments  and calls the
/// think function of CompileBot, outputting "UP", "DOWN", "LEFT", or "RIGHT"
///
/// The expected format of each argument is as follows:
///
/// a bool indicating if the bot is player one, "true"
/// or "false".
///
/// the current tick as an integer
///
/// The size of each row on the board and all the cells from top to bottom
/// separated by spaces.
///
/// Player one segments as numbers separated by spaces. The first pair of
/// numbers is the head. There must be an even count of numbers.
///
/// Same as player one segments but represents the second player
///
/// Assumes all player segments are valid (i.e they are within the given cells)
int main(int argc, char *argv[]) {
  const int EXPECTED_ARGC = 6;
  if (argc != EXPECTED_ARGC) {
    // subtract EXPECTED_ARGC by 1 because the binary itself is a argument
    throw std::invalid_argument(
        "Expected " + std::to_string(EXPECTED_ARGC - 1) +
        " arguments, received " + std::to_string(argc - 1));
  };

  bool is_player_one = reader::is_player_one(argv[1]);

  int current_tick = reader::current_tick(argv[2]);

  Cells cells = reader::read_cells(argv[3]);

  std::vector<Pos> player_one_segments = reader::read_player_segments(argv[4]);

  std::vector<Pos> player_two_segments = reader::read_player_segments(argv[5]);

  CompileBot bot;
  Grid grid(is_player_one, current_tick, cells, player_one_segments,
            player_two_segments);

  std::cout << (dir_to_str(bot.think(grid))) << std::endl;
}
