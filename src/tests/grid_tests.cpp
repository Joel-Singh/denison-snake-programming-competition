#include <gtest/gtest.h>
#include "../grid.cpp"

TEST(Grid, get_methods) {
  Cells cells(10);

  cells.set(3, 3, Cell::FRUIT);

  Grid grid(cells, false);

  EXPECT_EQ(grid.get_height(), 10);
  EXPECT_EQ(grid.get_width(), 10);

  EXPECT_EQ(grid.get(5, 5), Cell::EMPTY);
  EXPECT_EQ(grid.get(3, 3), Cell::FRUIT);

  EXPECT_THROW(grid.get(10, 10), std::logic_error);
  EXPECT_THROW(grid.get(-1, 10), std::logic_error);
  EXPECT_THROW(grid.get(5, -1), std::logic_error);
}

TEST(Grid, find_methods) {
  Cells cells(10);

  cells.set(0, 0, Cell::FRUIT);
  cells.set(1, 1, Cell::FRUIT);
  cells.set(2, 2, Cell::FRUIT);

  // The first number is the y value, not the x
  cells.set(0, 9, Cell::PLAYER_ONE);
  cells.set(1, 9, Cell::PLAYER_ONE);
  cells.set(2, 9, Cell::PLAYER_ONE);
  cells.set(3, 9, Cell::PLAYER_ONE_HEAD);

  cells.set(0, 8, Cell::PLAYER_TWO);
  cells.set(1, 8, Cell::PLAYER_TWO);
  cells.set(2, 8, Cell::PLAYER_TWO);
  cells.set(3, 8, Cell::PLAYER_TWO_HEAD);

  Grid grid(cells, true);

  EXPECT_EQ(grid.find_fruits(), std::vector<Pos>({
    Pos(0, 0),
    Pos(1, 1),
    Pos(2, 2)
  }));

  EXPECT_EQ(grid.find_self_head(), Pos(3, 9));
  EXPECT_EQ(grid.find_self_positions(), std::vector<Pos>({
    Pos(0, 9),
    Pos(1, 9),
    Pos(2, 9),
    Pos(3, 9)
  }));

  EXPECT_EQ(grid.find_other_head(), Pos(3, 8));

  EXPECT_EQ(grid.find_other_positions(), std::vector<Pos>({
    Pos(0, 8),
    Pos(1, 8),
    Pos(2, 8),
    Pos(3, 8)
  }));
}

