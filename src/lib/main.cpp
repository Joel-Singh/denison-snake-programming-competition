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
#include "lib/split_by_char.h"
#include "my_bot.h"
#include "tournament/create_round_robin.h"
#include "tournament/file_to_str.h"
#include "tournament/match_vec_to_str.h"
#include "tournament/run_bot.h"
#include "tournament/str_to_match_vec.h"
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace fs = std::filesystem;
using namespace std;

const sf::Time GAME_TICK_TIME = sf::seconds(0.2);
const sf::Color BACKGROUND_COLOR = sf::Color::Black;

const Pos player_one_start = Pos(2, CELL_SIZE / 2);
const Pos player_two_start = Pos(CELL_SIZE - 3, CELL_SIZE / 2);

GameState run_two_bot_game(Cells &cells, std::vector<Pos> &player_one_segments,
                           std::vector<Pos> &player_two_segments,
                           const Bot *player_one, const Bot *player_two,
                           const unsigned int game_ticks);

/// \brief runs a round robin rounmanet with the compiled bots in
/// ./src/tournament/bots.
///
/// The bots in tournament/bots should be named as
/// first-last-name. `first` and `last` is the creator's real name and `name` is
/// their bots chosen name.
///
/// Generates /tmp/du_slither_current_matches.txt that contains all matches.
/// Here is an example of the format:
///
/// first-last-name first-last-name PlayerOneWon
/// first-last-name first-last-name NotRun
/// first-last-name first-last-name NotRun
/// ...
///
/// The first bot and second bots are the bots going against eachother, and the
/// third is the match result corresponding to \ref MatchResult.
///
/// Creating a file like this means that the program can be shut down and run
/// again later. Also provides protection for if the software crashes, it can
/// just be restarted.
///
/// If /tmp/du_slither_current_matches.txt exists then the program runs matches
/// based on that.
int main(int argc, char *argv[]) {
  std::srand(time(NULL)); // Seed rng with current time
  string du_slither_current_matches_path =
      "/tmp/du_slither_current_matches.txt";

  // Generate matches from /tmp/du_slither_current_matches.txt OR create from
  // the current pool of competitiors and write to
  // /tmp/du_slither_current_matches.txt
  ifstream current_matches_txt{du_slither_current_matches_path};
  vector<Match> matches;
  if (current_matches_txt) {
    string match_str = file_to_str(current_matches_txt);
    matches = str_to_match_vec(match_str);

  } else {
    vector<string> competitors;
    std::string bot_path = "./src/tournament/bots";

    for (const auto &entry : fs::directory_iterator(bot_path)) {
      string name = split_by_char(entry.path(), '/').back();
      competitors.push_back(name);
    }

    matches = create_round_robin(competitors);
    std::ofstream outf{du_slither_current_matches_path};
    outf << match_vec_to_str(matches);
  }

  // for (const auto &match : matches) {
  //   std::cout << "std::get<0>(match)" << (std::get<0>(match)) << std::endl;
  //   std::cout << "std::get<1>(match)" << (std::get<1>(match)) << std::endl;
  //   std::cout << "------------------------------" << std::endl;
  // }
  //
  // // Create all of our game data
  // sf::Clock clock;
  // Input input;
  //
  // GameState game_state = GameState::ON_GOING;
  // unsigned int game_ticks = 0;
  //
  // std::vector<Pos> player_one_segments = {player_one_start};
  // std::vector<Pos> player_two_segments = {player_two_start};
  //
  // Cells cells =
  //     create_from_segments(CELL_SIZE, player_one_segments,
  //     player_two_segments);
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
