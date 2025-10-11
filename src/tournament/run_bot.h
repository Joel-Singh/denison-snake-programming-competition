#pragma once

#include "direction.h"
#include "lib/cells.h"
#include "pos.h"
#include <string>
#include <tuple>
#include <vector>

using namespace std;

enum class BotFailureReason { BOT_OVER_TIME_LIMIT, FAILED_TO_OUTPUT_DIRECTION };

class BotFailureException : public std::exception {
private:
  BotFailureReason reason; // handle our own string

public:
  BotFailureException(BotFailureReason reason) : reason(reason) {}

  // std::exception::what() returns a const char*, so we must as well
  const char *what() const noexcept override {
    if (reason == BotFailureReason::BOT_OVER_TIME_LIMIT) {
      return "Bot over time limit";
    } else {
      return "Failed to ouput direction";
    }
  }

  const BotFailureReason get_reason() { return reason; }
};

/// \brief runs the bot binary using the limits described in game_settings.h. If
/// the bot could not be run or it runs over limits, a runtime_error is thrown.
///
/// this function will take control from the main control path, until after \ref
/// TIME_LIMIT or the returns a response.
Direction run_bot(string path_to_bot, bool is_player_one, int current_tick,
                  Cells cells, vector<Pos> player_one_segments,
                  vector<Pos> player_two_segments);
