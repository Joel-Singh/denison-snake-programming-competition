#pragma once

#include <string>

using namespace std;

enum class MatchResult {
  PlayerOneWon,
  PlayerTwoWon,
  Draw,
  NotRun,
};

string match_result_to_str(MatchResult match_result);
MatchResult str_to_match_result(string const &match_result);

/// \brief represents a match. player_one and player_two follow the
/// first-last-name convention.
class Match {
public:
  string get_player_one() const;
  string get_player_two() const;
  MatchResult match_result;

  Match(string player_one, string player_two, MatchResult match_result);

  bool operator==(const Match &other) const;

  Match &operator=(Match const &other);

  friend ostream &operator<<(std::ostream &out, const Match &match);

private:
  string player_one;
  string player_two;
};
