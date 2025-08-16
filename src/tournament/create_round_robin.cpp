#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

vector<tuple<string, string>> create_round_robin(vector<string> competitors) {
  if (competitors.size() < 2) {
    throw invalid_argument("`" + to_string(competitors.size()) + "`" +
                           " is not enough competitors! (atleast 2)");
  }

  vector<tuple<string, string>> matches;
  for (int i = 0; i < competitors.size(); i++) {
    for (int j = i + 1; j < competitors.size(); j++) {
      matches.push_back({competitors.at(i), competitors.at(j)});
    }
  }

  return matches;
}
