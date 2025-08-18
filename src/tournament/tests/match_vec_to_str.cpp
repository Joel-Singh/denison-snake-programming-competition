#include "tournament/match_vec_to_str.h"
#include <gtest/gtest.h>

TEST(match_vec_to_str, makes_empty_string_on_empty_vec) {
  vector<Match> match_vec = {};

  ASSERT_EQ(match_vec_to_str(match_vec), "");
}

TEST(match_vec_to_str, makes_string_on_nonempty_vec) {
  vector<Match> match_vec = {
      Match("Beauty", "Beast", MatchResult::NotRun),
      Match("Hansel", "Gretel", MatchResult::Draw),
      Match("Alice", "Bob", MatchResult::PlayerOneWon),
      Match("Jack", "Jill", MatchResult::PlayerTwoWon),
  };

  ASSERT_EQ(match_vec_to_str(match_vec), "Beauty Beast NotRun\n"
                                         "Hansel Gretel Draw\n"
                                         "Alice Bob PlayerOneWon\n"
                                         "Jack Jill PlayerTwoWon");
}
