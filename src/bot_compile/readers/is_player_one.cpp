#include "is_player_one.h"
#include <stdexcept>
#include <string>

namespace reader {
/// \brief returns true if string is "true", false if string is "false". Else,
/// throws.
bool is_player_one(std::string str) {
  if (str == "true") {
    return true;
  } else if (str == "false") {
    return false;
  } else {
    throw std::invalid_argument(str + " is not false or true");
  }
}

} // namespace reader
