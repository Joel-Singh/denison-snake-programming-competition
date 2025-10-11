#include "run_bot.h"
#include "game_settings.h"
#include "tournament/writers/write_cells.h"
#include "tournament/writers/write_segments.h"
#include <chrono>
#include <fcntl.h>
#include <iomanip>
#include <stdexcept>
#include <stdio.h>
#include <thread>
#include <unistd.h>

/// \brief returns str quoted
static string quoted(string str) { return "'" + str + "'"; }

Direction run_bot(string path_to_bot, bool is_player_one, int current_tick,
                  Cells cells, vector<Pos> player_one_segments,
                  vector<Pos> player_two_segments) {
  string is_player_one_str = is_player_one ? "true" : "false";
  string current_tick_str = to_string(current_tick);
  string cells_str = writer::write_cells(cells);
  string player_one_segments_str = writer::write_segments(player_one_segments);
  string player_two_segments_str = writer::write_segments(player_two_segments);

  auto start_time = chrono::system_clock::now();

  FILE *bot_binary_stdout = popen(
      (path_to_bot + " " + quoted(is_player_one_str) + " " +
       quoted(current_tick_str) + " " + quoted(cells_str) + " " +
       quoted(player_one_segments_str) + " " + quoted(player_two_segments_str))
          .c_str(),
      "r");

  /// Example for using popen here:
  /// https://web.archive.org/web/20250821042717/https://c-for-dummies.com/blog/?p=1418
  if (bot_binary_stdout == NULL) {
    throw runtime_error("The bot binary itself could not be run");
  }

  // Set the std out of bot binary to not be blocking when callling getc, so
  // that we can constantly check if there's been output. Referenced primarily
  // this to do so: https://stackoverflow.com/a/30548692/22985180
  auto file_descriptor = fileno(bot_binary_stdout);
  auto original_flags = fcntl(file_descriptor, F_GETFL);
  fcntl(file_descriptor, F_SETFL, original_flags | O_NONBLOCK);

  while (true) {
    auto now = chrono::system_clock::now();
    auto time_passed = now - start_time;
    if (time_passed > TIME_LIMIT) {
      throw BotFailureException(BotFailureReason::BOT_OVER_TIME_LIMIT);
    }

    int ch;
    if ((ch = getc(bot_binary_stdout)) != EOF) {
      ungetc(ch, bot_binary_stdout);
      break;
    }

    this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  string chosen_direction = "";

  int ch;
  while ((ch = getc(bot_binary_stdout)) != EOF)
    chosen_direction += ch;
  pclose(bot_binary_stdout);

  if (chosen_direction == "") {
    throw BotFailureException(BotFailureReason::FAILED_TO_OUTPUT_DIRECTION);
  } else {
    return str_to_dir(chosen_direction);
  }
}
