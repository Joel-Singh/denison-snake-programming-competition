#include "../str_to_match_vec.h"
#include <gtest/gtest.h>

TEST(str_to_match_vec, returns_empty_vec_on_empty_str) {
  vector<Match> empty_match_vec = {};
  ASSERT_EQ(str_to_match_vec(""), empty_match_vec);
}

TEST(str_to_match_vec, returns_correct_vec_on_nonempty_str) {
  vector<Match> match_vec = {
      Match("Beauty", "Beast", MatchResult::NotRun),
      Match("Hansel", "Gretel", MatchResult::Draw),
      Match("Alice", "Bob", MatchResult::PlayerOneWon),
      Match("Jack", "Jill", MatchResult::PlayerTwoWon),
  };

  ASSERT_EQ(str_to_match_vec("Beauty Beast NotRun\n"
                             "Hansel Gretel Draw\n"
                             "Alice Bob PlayerOneWon\n"
                             "Jack Jill PlayerTwoWon"),
            match_vec);
}
