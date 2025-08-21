#include "run_bot.h"
#include "game_settings.h"
#include "tournament/writers/write_cells.h"
#include "tournament/writers/write_segments.h"
#include <chrono>
#include <stdio.h>
#include <thread>

/// \brief returns str quoted
static string quoted(string str) { return "'" + str + "'"; }

/// \brief runs the bot binary using the limits described in game_settings.h. If
/// the first element of the tuple is the empty string, then the bot ran
/// successfully under the limits and the second element, the direction, can be
/// used. Otherwise, the bot did not run successfully and the content of the
/// string is what went wrong.
tuple<string, Direction> run_bot(string path_to_bot, bool is_player_one,
                                 int current_tick, Cells cells,
                                 vector<Pos> player_one_segments,
                                 vector<Pos> player_two_segments) {
  string is_player_one_str = is_player_one ? "true" : "false";
  string current_tick_str = to_string(current_tick);
  string cells_str = writer::write_cells(cells);
  string player_one_segments_str = writer::write_segments(player_one_segments);
  string player_two_segments_str = writer::write_segments(player_two_segments);

  FILE *p = popen((path_to_bot + " " + quoted(is_player_one_str) + " " +
                   quoted(current_tick_str) + " " + quoted(cells_str) + " " +
                   quoted(player_one_segments_str) + " " +
                   quoted(player_two_segments_str))
                      .c_str(),
                  "r");

  /// Example for using popen here:
  /// https://web.archive.org/web/20250821042717/https://c-for-dummies.com/blog/?p=1418
  if (p == NULL) {
    return {"Couldn't run bot", Direction::UP};
  }

  string chosen_direction = "";

  int ch;
  while ((ch = fgetc(p)) != EOF)
    chosen_direction += ch;
  pclose(p);

  if (chosen_direction == "") {
    // Return placeholder
    return {"binary did not return a direction", Direction::UP};
  } else {
    return {"", str_to_dir(chosen_direction)};
  }
}
