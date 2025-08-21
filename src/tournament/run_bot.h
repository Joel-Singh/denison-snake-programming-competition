#pragma once

#include "direction.h"
#include "lib/cells.h"
#include "pos.h"
#include <string>
#include <tuple>
#include <vector>

using namespace std;

tuple<string, Direction> run_bot(string path_to_bot, bool is_player_one,
                                 int current_tick, Cells cells,
                                 vector<Pos> player_one_segments,
                                 vector<Pos> player_two_segments);
