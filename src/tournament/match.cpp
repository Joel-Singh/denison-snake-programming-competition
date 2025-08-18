#include "match.h"

using namespace std;

string Match::get_player_one() const { return this->player_one; }
string Match::get_player_two() const { return this->player_two; }

Match::Match(string player_one, string player_two, MatchResult match_result)
    : player_one(player_one), player_two(player_two),
      match_result(match_result) {};

bool Match::operator==(const Match &other) const {
  return this->player_one == other.get_player_one() &&
         this->player_two == other.get_player_two() &&
         this->match_result == other.match_result;
}

std::ostream &operator<<(std::ostream &out, const Match &match) {
  string result;

  if (match.match_result == MatchResult::PlayerOneWon) {
    result = "PlayerOneWon";
  } else if (match.match_result == MatchResult::PlayerTwoWon) {
    result = "PlayerTwoWon";
  } else if (match.match_result == MatchResult::Draw) {
    result = "Draw";
  } else {
    result = "NotRun";
  }

  out << match.get_player_one() << string(" vs. ") << match.get_player_two()
      << string("result: ") << result;

  return out;
}
