#include "bot_compile/writers/write_cells.h"
#include <gtest/gtest.h>

using namespace writer;

TEST(writers, write_cells) {
  Cells cells(3);

  cells.set(0, 2, Cell::FRUIT);
  cells.set(1, 0, Cell::PLAYER_ONE_HEAD);

  ASSERT_EQ(
      writer::write_cells(cells),
      "3 FRUIT EMPTY EMPTY EMPTY EMPTY EMPTY EMPTY PLAYER_ONE_HEAD EMPTY");
}
