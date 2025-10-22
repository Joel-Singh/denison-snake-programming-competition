#pragma once

/// \brief represents what the other player is for initialization to go
/// accordingly.
enum class PlayerType { EvilBot, MyBot, Manual };

struct Arguments {
  const bool infinite;
  const PlayerType player_type;
  bool operator==(const Arguments &other) const {
    return infinite == other.infinite && player_type == other.player_type;
  };
};

/// \brief Figures out what player 2 should be and whether --infinite was passed
/// from commandline args, throwing if args is wrong and returning `Arguments`
/// otherwise.
Arguments get_commandline_args(int argc, char *argv[]);
