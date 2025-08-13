#include "bot_compile/compile_bot.h"
#include "direction.h"
#include "game_settings.h"
#include "lib/cells.h"
#include "lib/create_from_segments.h"
#include "pos.h"
#include <vector>

int main(int argc, char *argv[]) {
  std::vector<Pos> player_one_segments = {Pos(0, 0)};
  std::vector<Pos> player_two_segments = {Pos(1, 0)};
  Cells cells =
      create_from_segments(CELL_SIZE, player_one_segments, player_two_segments);

  CompileBot bot;
  Grid grid(false, 0, cells, player_one_segments, player_two_segments);

  std::cout << dir_to_str(bot.think(grid));
}
