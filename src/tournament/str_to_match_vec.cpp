#include "str_to_match_vec.h"
#include "lib/split_by_char.h"
#include <iostream>
#include <stdexcept>

vector<Match> str_to_match_vec(string str) {
  vector<Match> matches;
  vector<string> matches_str = split_by_char(str, '\n');

  for (string match_str : matches_str) {
    vector<string> match_split = split_by_char(match_str, ' ');

    if (match_split.size() != 3) {
      throw invalid_argument('`' + match_str + '`' +
                             " is not a valid match, should be formatted as "
                             "`first-last-name first-last-name match_result`");
    }

    matches.push_back(Match(match_split.at(0), match_split.at(1),
                            str_to_match_result(match_split.at(2))));
  }

  return matches;
}
