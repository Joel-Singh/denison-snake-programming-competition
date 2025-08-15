#include "bot_compile/readers/read_player_segments.h"
#include "pos.h"
#include <stdexcept>
#include <vector>

namespace reader {

/// Reads the segments of a player from str. str should be integers separated by
/// spaces. every two numbers is interpreted as a position, throws if there is
/// an odd count of numbers.
std::vector<Pos> read_player_segments(std::string const &str) {
  std::vector<Pos> player_segments;

  if (str.size() == 0) {
    throw std::invalid_argument("Can't read player segments from empty string");
  }

  int i = 0;
  while (true) {
    std::string first_number_str = "";
    while (i != str.size() && str.at(i) != ' ') {
      first_number_str += str.at(i);
      i++;
    }

    int first_number_int = std::stoi(first_number_str);

    if (i == str.size()) {
      throw std::invalid_argument(
          "Odd count of numbers when reading player segments");
    } else {
      // move i from ' '
      i++;
    }

    std::string second_number_str = "";
    while (i != str.size() && str.at(i) != ' ') {
      second_number_str += str.at(i);
      i++;
    }

    int second_number_int = std::stoi(second_number_str);

    player_segments.push_back(Pos(first_number_int, second_number_int));

    if (i == str.size()) {
      break;
    } else {
      // move i from ' '
      i++;
    }
  }

  return player_segments;
}

} // namespace reader
