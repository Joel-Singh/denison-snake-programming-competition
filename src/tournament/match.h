#pragma once

#include <string>

using namespace std;

enum class MatchResult {
  PlayerOneWon,
  PlayerTwoWon,
  Draw,
  NotRun,
};

/// \brief represents a match. player_one and player_two follow the
/// first-last-name convention.
class Match {
public:
  string get_player_one() const;
  string get_player_two() const;
  const MatchResult match_result;

  Match(string player_one, string player_two, MatchResult match_result);

  bool operator==(const Match &other) const;
  friend ostream &operator<<(std::ostream &out, const Match &match);

private:
  string player_one;
  string player_two;
};
