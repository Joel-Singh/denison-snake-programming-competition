#include "split_by_char.h"

vector<string> split_by_char(string const &str, char const &ch) {
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
