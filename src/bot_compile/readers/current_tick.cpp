#include <string>

namespace reader {
/// \brief takes in string and converts it to an integer, throws if malformed
/// input on the call sto std::stoi
int current_tick(std::string str) { return std::stoi(str); }
} // namespace reader
