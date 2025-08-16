#include "assert.h"
#include "cell.h"
#include "evil_bot.h"
#include "game_settings.h"
#include "lib/cells.h"
#include "lib/compute_game_logic.h"
#include "lib/create_from_segments.h"
#include "lib/draw_cells.h"
#include "lib/draw_text.h"
#include "lib/get_player_from_args.h"
#include "lib/input.h"
#include "my_bot.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>

const sf::Time GAME_TICK_TIME = sf::seconds(0.2);
const sf::Color BACKGROUND_COLOR = sf::Color::Black;

const Pos player_one_start = Pos(2, CELL_SIZE / 2);
const Pos player_two_start = Pos(CELL_SIZE - 3, CELL_SIZE / 2);

GameState run_two_bot_game(Cells &cells, std::vector<Pos> &player_one_segments,
                           std::vector<Pos> &player_two_segments,
                           const Bot *player_one, const Bot *player_two,
                           const unsigned int game_ticks);

int main(int argc, char *argv[]) {
  std::srand(time(NULL)); // Seed rng with current time
}

GameState run_two_bot_game(Cells &cells, std::vector<Pos> &player_one_segments,
                           std::vector<Pos> &player_two_segments,
                           const Bot *player_one, const Bot *player_two,
                           const unsigned int game_ticks) {

  assert(player_one != nullptr);
  assert(player_two != nullptr);

  Grid player_one_grid(true, game_ticks, cells, player_one_segments,
                       player_two_segments);
  Grid player_two_grid(false, game_ticks, cells, player_one_segments,
                       player_two_segments);

  Direction player_one_dir = player_one->think(player_one_grid);
  Direction player_two_dir = player_two->think(player_two_grid);

  GameState game_state =
      compute_game_logic(cells, game_ticks, player_one_dir, player_two_dir,
                         player_one_segments, player_two_segments);

  return game_state;
}
