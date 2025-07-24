#include "lib/cells.h"
#include <gtest/gtest.h>
#include <stdexcept>

TEST(Cells, get) {
  Cells cells(10);

  EXPECT_EQ(cells.get(0, 0), Cell::EMPTY);
  EXPECT_EQ(cells.get(1, 1), Cell::EMPTY);
  EXPECT_EQ(cells.get(2, 2), Cell::EMPTY);
  EXPECT_EQ(cells.get(9, 9), Cell::EMPTY);

  EXPECT_EQ(cells.get(Pos(0, 0)), Cell::EMPTY);
  EXPECT_EQ(cells.get(Pos(1, 1)), Cell::EMPTY);
  EXPECT_EQ(cells.get(Pos(2, 2)), Cell::EMPTY);
  EXPECT_EQ(cells.get(Pos(9, 9)), Cell::EMPTY);

  EXPECT_THROW(cells.get(10, 0), std::logic_error);
}

TEST(Cells, height_and_width) {
  Cells cells(5);

  EXPECT_EQ(cells.height(), 5);
  EXPECT_EQ(cells.width(), 5);
}

TEST(Cells, set) {
  Cells cells(5);

  cells.set(2, 3, Cell::FRUIT);
  EXPECT_EQ(cells.get(2, 3), Cell::FRUIT);

  cells.set(Pos(1, 4), Cell::FRUIT);
  EXPECT_EQ(cells.get(1, 4), Cell::FRUIT);
}
