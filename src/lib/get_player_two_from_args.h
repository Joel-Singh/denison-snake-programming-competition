#pragma once

/// \brief represents what the other player is for initialization to go
/// accordingly.
enum PlayerTwo { EvilBot, MyBot, Manual };

/// \brief Figures out what player 2 should be from commandline args, throwing
/// if args is wrong
PlayerTwo get_player_2_from_commandline_args(int argc, char *argv[]);
