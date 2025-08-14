#include "bot_compile/compile_bot.h"
#include "direction.h"
#include "game_settings.h"
#include "lib/cells.h"
#include "lib/create_from_segments.h"
#include "pos.h"
#include <vector>

/// \brief Takes in the current state of the board from std input and calls the
/// think function of CompileBot, outputting "UP", "DOWN", "LEFT", or "RIGHT"
///
/// The expected format of std input is as follows, with each parameter
/// separated by a newline:
///
/// a bool indicating if the bot is player one, "true"
/// or "false". the current tick as an integer The size of each row on the board
///
/// All the cells from top to bottom separated by spaces
///
/// Player one segments as numbers separated by spaces. The first pair of
/// numbers is the head. There must be an even count of numbers.
///
/// Same as player one segments but represents player two segments.
int main(int argc, char *argv[]) {
  std::vector<Pos> player_one_segments = {Pos(0, 0)};
  std::vector<Pos> player_two_segments = {Pos(1, 0)};
  Cells cells =
      create_from_segments(CELL_SIZE, player_one_segments, player_two_segments);

  CompileBot bot;
  Grid grid(false, 0, cells, player_one_segments, player_two_segments);

  std::cout << dir_to_str(bot.think(grid));
}
