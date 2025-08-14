#pragma once

#include <string>

namespace reader {
/// \brief takes in string and converts it to an integer, throws if malformed
/// input
int current_tick(std::string str);
} // namespace reader
