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
#include <optional>
#include <stdexcept>

namespace fs = std::filesystem;
using namespace std;

const sf::Time GAME_TICK_TIME = sf::seconds(0.2);
const sf::Color BACKGROUND_COLOR = sf::Color::Black;

const Pos player_one_start = Pos(2, GRID_SIZE / 2);
const Pos player_two_start = Pos(GRID_SIZE - 3, GRID_SIZE / 2);

GameState run_two_bot_game(Cells &cells, std::vector<Pos> &player_one_segments,
                           std::vector<Pos> &player_two_segments,
                           Direction player_one_dir, Direction player_two_dir,
                           const unsigned int game_ticks);
string get_path_to_bot(string name);

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

  string player_one;
  string player_two;

  // Get the first match not run
  bool found = false;
  for (Match match : matches) {
    if (match.match_result == MatchResult::NotRun) {
      player_one = get_path_to_bot(match.get_player_one());
      player_two = get_path_to_bot(match.get_player_two());
      found = true;
    }

    if (found) {
      break;
    }
  }

  if (!found) {
    throw runtime_error("Not matches to run");
  }

  // Create all of our game data
  sf::RenderWindow window(sf::VideoMode({200, 200}), "Denison Snake!");
  window.setFramerateLimit(60);

  sf::Clock clock;
  Input input;

  GameState game_state = GameState::ON_GOING;
  unsigned int game_ticks = 0;

  std::vector<Pos> player_one_segments = {player_one_start};
  std::vector<Pos> player_two_segments = {player_two_start};

  Cells cells =
      create_from_segments(GRID_SIZE, player_one_segments, player_two_segments);

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();

      if (const auto *resized = event->getIf<sf::Event::Resized>()) {
        // update the view to the new size of the window
        sf::FloatRect visibleArea({0.f, 0.f}, sf::Vector2f(resized->size));
        window.setView(sf::View(visibleArea));
      }

      update_input(event, input);
    }

    if (input.was_L_pressed && game_state == GameState::ON_GOING) {
      optional<Direction> direction_one;
      optional<BotFailureException> one_bot_failure;

      optional<Direction> direction_two;
      optional<BotFailureException> two_bot_failure;

      try {
        direction_one = run_bot(player_one, true, game_ticks, cells,
                                player_one_segments, player_two_segments);
      } catch (BotFailureException ex) {
        one_bot_failure = ex;
      }

      try {
        direction_two = run_bot(player_two, false, game_ticks, cells,
                                player_one_segments, player_two_segments);
      } catch (BotFailureException ex) {
        two_bot_failure = ex;
      }

      if (one_bot_failure.has_value() && two_bot_failure.has_value()) {
        cout << "Both bots failed to run" << endl;
        cout << player_one << ": " << one_bot_failure->what() << endl;
        cout << player_two << ": " << two_bot_failure->what() << endl;

        game_state = GameState::DRAW;
      } else if (one_bot_failure.has_value()) {
        cout << player_one << " failed to run: " << one_bot_failure->what()
             << endl;

        game_state = GameState::PLAYER_TWO_WON;
      } else if (two_bot_failure.has_value()) {
        cout << player_two << " failed to run: " << two_bot_failure->what()
             << endl;

        game_state = GameState::PLAYER_ONE_WON;
      }

      if (!one_bot_failure.has_value() && !two_bot_failure.has_value()) {
        run_two_bot_game(cells, player_one_segments, player_two_segments,
                         direction_one.value(), direction_two.value(),
                         game_ticks);
      }

      input.was_L_pressed = false;
      game_ticks++;
    }

    window.clear(BACKGROUND_COLOR);
    draw_cells(window, cells);
    window.display();
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
                           Direction player_one_dir, Direction player_two_dir,
                           const unsigned int game_ticks) {
  Grid player_one_grid(true, game_ticks, cells, player_one_segments,
                       player_two_segments);
  Grid player_two_grid(false, game_ticks, cells, player_one_segments,
                       player_two_segments);

  GameState game_state =
      compute_game_logic(cells, game_ticks, player_one_dir, player_two_dir,
                         player_one_segments, player_two_segments);

  return game_state;
}

// \brief Gets the path to a bot binary, assuming the cwd is the root of the
// project
string get_path_to_bot(string name) { return "./src/tournament/bots/" + name; }
