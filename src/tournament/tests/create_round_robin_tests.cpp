#include "tournament/create_round_robin.h"
#include "tournament/match.h"
#include <gtest/gtest.h>

using namespace std;

TEST(create_round_robin, throws_on_not_enough_competitors) {
  EXPECT_THROW(create_round_robin(vector<string>()), invalid_argument);
}

TEST(create_round_robin, with_two_competitors) {
  vector<Match> expected_matches = {Match("a", "b", MatchResult::NotRun)};
  EXPECT_EQ(create_round_robin({"a", "b"}), expected_matches);
}

TEST(create_round_robin, with_three_competitors) {
  vector<Match> expected_matches = {Match("a", "b", MatchResult::NotRun),
                                    Match("a", "c", MatchResult::NotRun),
                                    Match("b", "c", MatchResult::NotRun)};

  EXPECT_EQ(create_round_robin({"a", "b", "c"}), expected_matches);
}
