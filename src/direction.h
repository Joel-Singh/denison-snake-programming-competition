///
/// \file
///

#pragma once

#include <string>

/// \brief Represents a direction and is returned by your bot in \ref
/// MyBot::think
enum class Direction { UP, DOWN, LEFT, RIGHT };

std::string dir_to_str(Direction dir);
