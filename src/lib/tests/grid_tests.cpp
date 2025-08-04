#include "lib/create_from_segments.h"
#include "grid.h"
#include <gtest/gtest.h>

TEST(Grid, get_methods) {
  Cells cells(10);

  cells.set(3, 3, Cell::FRUIT);

  Grid grid(false, cells, std::vector<Pos>(), std::vector<Pos>());

  EXPECT_EQ(grid.get_height(), 10);
  EXPECT_EQ(grid.get_width(), 10);

  EXPECT_EQ(grid.get(5, 5), Cell::EMPTY);
  EXPECT_EQ(grid.get(3, 3), Cell::FRUIT);

  EXPECT_THROW(grid.get(10, 10), std::logic_error);
  EXPECT_THROW(grid.get(-1, 10), std::logic_error);
  EXPECT_THROW(grid.get(5, -1), std::logic_error);
}

TEST(Grid, find_methods) {
  std::vector<Pos> player_one_segments = {Pos(3, 9), Pos(2, 9), Pos(1, 9),
                                          Pos(0, 9)};

  std::vector<Pos> player_two_segments = {Pos(3, 8), Pos(2, 8), Pos(1, 8),
                                          Pos(0, 8)};
  Cells cells =
      create_from_segments(10, player_one_segments, player_two_segments);

  cells.set(0, 0, Cell::FRUIT);
  cells.set(1, 1, Cell::FRUIT);
  cells.set(2, 2, Cell::FRUIT);

  Grid grid(true, cells, player_one_segments, player_two_segments);

  EXPECT_EQ(grid.find_fruits(),
            std::vector<Pos>({Pos(0, 0), Pos(1, 1), Pos(2, 2)}));

  EXPECT_EQ(grid.find_self_head(), Pos(3, 9));
  EXPECT_EQ(grid.find_self_positions(), player_one_segments);

  EXPECT_EQ(grid.find_other_head(), Pos(3, 8));
  EXPECT_EQ(grid.find_other_positions(), player_two_segments);
}
