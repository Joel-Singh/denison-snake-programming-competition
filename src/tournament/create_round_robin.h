#include "tournament/match.h"
#include <string>
#include <tuple>
#include <vector>

using namespace std;

/// Create pairings of the passed in strings for a round robin tournament.
/// Throws if there are less than 2 competitors.
vector<Match> create_round_robin(vector<string> competitors);
