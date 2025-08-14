#include "bot_compile/readers/read_cells.h"
#include <gtest/gtest.h>

using namespace reader;

TEST(reader_tests, read_cells_correct_input_cases_simplest) {
  Cells cells = read_cells("1 EMPTY");

  EXPECT_EQ(cells.get(0, 0), Cell::EMPTY);
  EXPECT_EQ(cells.height(), 1);
  EXPECT_EQ(cells.width(), 1);
}

TEST(reader_tests, read_cells_correct_input_cases_complicated) {
  Cells cells =
      read_cells("3 EMPTY EMPTY EMPTY EMPTY EMPTY EMPTY PLAYER_ONE_HEAD "
                 "PLAYER_TWO_HEAD EMPTY");

  std::cout << cells.get(0, 2) << std::endl;
  std::cout << cells.get(1, 2) << std::endl;

  EXPECT_EQ(cells.get(0, 0), Cell::PLAYER_ONE_HEAD);
  EXPECT_EQ(cells.get(1, 0), Cell::PLAYER_TWO_HEAD);
}

TEST(reader_tests, read_cells_exceptions_str_size) {
  EXPECT_THROW(read_cells("1"), std::invalid_argument)
      << "Throw on str.size() < 3";
}

TEST(reader_tests, read_cells_exceptions_invalid_row_length) {
  EXPECT_THROW(read_cells("notanumber EMPTY"), std::invalid_argument)
      << "Throw on invalid row length";
}

TEST(reader_tests, read_cells_exceptions_no_cells_following_row_length) {
  EXPECT_THROW(read_cells("321"), std::invalid_argument)
      << "Throw on no cells following row length";
}

TEST(reader_tests, read_cells_exceptions_not_enough_cells) {
  EXPECT_THROW(read_cells("3 EMPTY EMPTY EMPTY EMPTY EMPTY"),
               std::invalid_argument)
      << "Throw on not enough cells for last row";
}

TEST(reader_tests, read_cells_exceptions_invalid_cell) {
  EXPECT_THROW(read_cells("3 EMPTY EMPTY NotAValidCell"), std::invalid_argument)
      << "Throw on invalid cell";
}
