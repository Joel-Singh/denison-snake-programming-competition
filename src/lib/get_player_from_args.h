#pragma once

/// \brief represents what the other player is for initialization to go
/// accordingly.
enum class PlayerType { EvilBot, MyBot, Manual };

/// \brief Figures out what player 2 should be from commandline args, throwing
/// if args is wrong
PlayerType get_player_from_args(int argc, char *argv[]);
