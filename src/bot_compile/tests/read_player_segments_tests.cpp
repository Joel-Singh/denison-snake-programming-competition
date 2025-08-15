#include "bot_compile/readers/read_player_segments.h"
#include <gtest/gtest.h>

using namespace reader;

TEST(reader_tests, read_player_segments_throws_on_empty) {
  ASSERT_THROW(read_player_segments(""), std::invalid_argument);
}

TEST(reader_tests, read_player_segments_throws_on_odd_count) {
  ASSERT_THROW(read_player_segments("3"), std::invalid_argument);
  ASSERT_THROW(read_player_segments("3 1 1"), std::invalid_argument);
  ASSERT_THROW(read_player_segments("3 1 1 3 3"), std::invalid_argument);
}

TEST(reader_tests, read_player_segments_simplest_case) {
  ASSERT_EQ(read_player_segments("3 1"), std::vector<Pos>({Pos(3, 1)}));
}

TEST(reader_tests, read_player_segments_complicated_case) {
  ASSERT_EQ(read_player_segments("3 1 3 9 2 6"),
            std::vector<Pos>({Pos(3, 1), Pos(3, 9), Pos(2, 6)}));
}
