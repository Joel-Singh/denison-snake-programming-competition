#include "bot_compile/readers/is_player_one.h"
#include <gtest/gtest.h>

using namespace reader;

TEST(reader_tests, is_player_one) {
  EXPECT_EQ(is_player_one("true"), true);
  EXPECT_EQ(is_player_one("false"), false);
  EXPECT_THROW(is_player_one("not true or false"), std::invalid_argument);
}

#include "bot_compile/tests/read_cells_tests.cpp"
#include "bot_compile/tests/read_player_segments_tests.cpp"
