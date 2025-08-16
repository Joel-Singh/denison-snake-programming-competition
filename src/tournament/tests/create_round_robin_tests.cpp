#include "tournament/create_round_robin.h"
#include <gtest/gtest.h>

using namespace std;

TEST(create_round_robin, throws_on_not_enough_competitors) {
  EXPECT_THROW(create_round_robin(vector<string>()), invalid_argument);
}

TEST(create_round_robin, with_two_competitors) {
  vector<tuple<string, string>> expected_match = {{"a", "b"}};
  EXPECT_EQ(create_round_robin({"a", "b"}), expected_match);
}

TEST(create_round_robin, with_three_competitors) {
  vector<tuple<string, string>> expected_match = {
      {"a", "b"}, {"a", "c"}, {"b", "c"}};
  EXPECT_EQ(create_round_robin({"a", "b", "c"}), expected_match);
}
