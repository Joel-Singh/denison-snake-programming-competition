#include "tournament/writers/write_cells.h"
#include "tournament/writers/write_segments.h"
#include <gtest/gtest.h>

using namespace writer;
using namespace std;

TEST(writers, write_cells) {
  Cells cells(3);

  cells.set(0, 2, Cell::FRUIT);
  cells.set(1, 0, Cell::PLAYER_ONE_HEAD);

  ASSERT_EQ(
      writer::write_cells(cells),
      "3 FRUIT EMPTY EMPTY EMPTY EMPTY EMPTY EMPTY PLAYER_ONE_HEAD EMPTY");
}

TEST(writers, write_segments) {
  vector<Pos> segments = {Pos(0, 0), Pos(1, 4), Pos(5, 8)};

  ASSERT_EQ(writer::write_segments(segments), "0 0 1 4 5 8");
}
