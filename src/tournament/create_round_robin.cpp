#include "create_round_robin.h"
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

vector<Match> create_round_robin(vector<string> competitors) {
  if (competitors.size() < 2) {
    throw invalid_argument("`" + to_string(competitors.size()) + "`" +
                           " is not enough competitors! (atleast 2)");
  }

  vector<Match> matches;
  for (int i = 0; i < competitors.size(); i++) {
    for (int j = i + 1; j < competitors.size(); j++) {
      string player_one = competitors.at(i);
      string player_two = competitors.at(j);

      matches.push_back(Match(player_one, player_two, MatchResult::NotRun));
    }
  }

  return matches;
}
