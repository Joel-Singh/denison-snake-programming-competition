#include "str_to_match_vec.h"
#include <iostream>
#include <stdexcept>

static vector<string> split_by_char(string const &str, char const &ch);
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

static vector<string> split_by_char(string const &str, char const &ch) {
  vector<string> splits = {};
  for (int i = 0; i < str.size(); i++) {
    string split = "";
    while (i != str.size() && str.at(i) != ch) {
      split += str.at(i);
      i++;
    }
    splits.push_back(split);
    split = "";
  }

  return splits;
}
