#pragma once

#include "pos.h"
#include <stdexcept>
#include <vector>

namespace reader {

/// Reads the segments of a player from str. str should be integers separated by
/// spaces. every two numbers is interpreted as a position, throws if there is
/// an odd count of numbers.
std::vector<Pos> read_player_segments(std::string const &str);

} // namespace reader
