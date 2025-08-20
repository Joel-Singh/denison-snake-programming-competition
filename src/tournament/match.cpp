#include "match.h"
#include <stdexcept>

using namespace std;
string match_result_to_str(MatchResult match_result) {
  if (match_result == MatchResult::PlayerOneWon) {
    return "PlayerOneWon";
  } else if (match_result == MatchResult::PlayerTwoWon) {
    return "PlayerTwoWon";
  } else if (match_result == MatchResult::Draw) {
    return "Draw";
  } else {
    return "NotRun";
  }
}

MatchResult str_to_match_result(string const &str) {
  if (str == "PlayerOneWon") {
    return MatchResult::PlayerOneWon;
  } else if (str == "PlayerTwoWon") {
    return MatchResult::PlayerTwoWon;
  } else if (str == "Draw") {
    return MatchResult::Draw;
  } else if (str == "NotRun") {
    return MatchResult::NotRun;
  }

  throw invalid_argument("`" + str + "`" + "is not a valid match result");
}

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

Match &Match::operator=(Match const &other) {
  this->player_one = other.player_one;
  this->get_player_two() = other.player_two;
  this->match_result = other.match_result;

  return *this;
}

std::ostream &operator<<(std::ostream &out, const Match &match) {
  out << match.get_player_one() << string(" vs. ") << match.get_player_two()
      << string(" result: ") << match_result_to_str(match.match_result);

  return out;
}
