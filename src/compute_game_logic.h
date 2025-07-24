#pragma once

#include "cell.h"
#include "cells.h"
#include <SFML/Graphics.hpp>

enum GameState { PLAYER_ONE_WON, PLAYER_TWO_WON, DRAW, ON_GOING };

GameState compute_game_logic(Cells &cells, const unsigned int game_ticks,
                             const Direction player_one_dir,
                             const Direction player_two_dir,
                             std::vector<Pos> &player_one_segments,
                             std::vector<Pos> &player_two_segments);
