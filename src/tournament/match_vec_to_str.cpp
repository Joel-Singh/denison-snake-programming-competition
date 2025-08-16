#include "tournament/match.h"
#include <string>
#include <vector>

string match_vec_to_str(vector<Match> const &match_vec) {
  string str = "";
  for (int i = 0; i < match_vec.size(); i++) {
    auto match = match_vec.at(i);
    str += match.get_player_one() + string(" ") + match.get_player_two() +
           string(" ") + match_result_to_str(match.match_result);

    bool not_last = i != match_vec.size() - 1;
    if (not_last) {
      str += "\n";
    }
  }

  return str;
}
