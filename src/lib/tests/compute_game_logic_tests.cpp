#include "lib/cells.h"
#include "lib/compute_game_logic.h"
#include "lib/create_from_segments.h"
#include <gtest/gtest.h>

TEST(compute_game_logic, head_movement) {
  std::vector<Pos> one_segments = {Pos(0, 0)};
  std::vector<Pos> two_segments = {Pos(0, 1)};

  Cells cells = create_from_segments(10, one_segments, two_segments);

  GameState game_state = compute_game_logic(
      cells, 0, Direction::RIGHT, Direction::RIGHT, one_segments, two_segments);

  ASSERT_EQ(game_state, GameState::ON_GOING);

  EXPECT_EQ(cells.get(0, 0), Cell::EMPTY);
  EXPECT_EQ(cells.get(0, 1), Cell::EMPTY);

  EXPECT_EQ(cells.get(1, 0), Cell::PLAYER_ONE_HEAD);
  EXPECT_EQ(cells.get(1, 1), Cell::PLAYER_TWO_HEAD);

  EXPECT_EQ(one_segments.front(), Pos(1, 0));
  EXPECT_EQ(two_segments.front(), Pos(1, 1));
}

TEST(compute_game_logic, multiple_segments_straight_movement) {
  std::vector<Pos> one_segments = {
      Pos(0, 5), Pos(0, 4), Pos(0, 3), Pos(0, 2), Pos(0, 1), Pos(0, 0),
  };

  std::vector<Pos> two_segments = {
      Pos(1, 5), Pos(1, 4), Pos(1, 3), Pos(1, 2), Pos(1, 1), Pos(1, 0),
  };

  Cells cells = create_from_segments(10, one_segments, two_segments);

  GameState game_state = compute_game_logic(
      cells, 0, Direction::UP, Direction::UP, one_segments, two_segments);

  ASSERT_EQ(game_state, GameState::ON_GOING);

  EXPECT_EQ(cells.get(0, 0), Cell::EMPTY);
  EXPECT_EQ(cells.get(1, 0), Cell::EMPTY);

  EXPECT_EQ(cells.get(0, 6), Cell::PLAYER_ONE_HEAD);
  EXPECT_EQ(cells.get(1, 6), Cell::PLAYER_TWO_HEAD);

  EXPECT_EQ(one_segments, std::vector<Pos>({Pos(0, 6), Pos(0, 5), Pos(0, 4),
                                            Pos(0, 3), Pos(0, 2), Pos(0, 1)}));

  EXPECT_EQ(two_segments, std::vector<Pos>({Pos(1, 6), Pos(1, 5), Pos(1, 4),
                                            Pos(1, 3), Pos(1, 2), Pos(1, 1)}));
}

TEST(compute_game_logic, moving_into_fruit_increases_length) {
  std::vector<Pos> one_segments = {
      Pos(0, 0),
  };

  std::vector<Pos> two_segments = {
      Pos(1, 0),
  };

  Cells cells = create_from_segments(10, one_segments, two_segments);
  cells.set(0, 1, Cell::FRUIT);

  GameState game_state = compute_game_logic(
      cells, 0, Direction::UP, Direction::UP, one_segments, two_segments);

  ASSERT_EQ(game_state, GameState::ON_GOING);
  ASSERT_EQ(one_segments.size(), 2);

  EXPECT_EQ(one_segments, std::vector<Pos>({Pos(0, 1), Pos(0, 0)}));
}

TEST(compute_game_logic, multiple_segments_curved_movement) {
  std::vector<Pos> one_segments = {
      Pos(1, 4), Pos(0, 4), Pos(0, 3), Pos(0, 2), Pos(0, 1), Pos(0, 0),
  };

  std::vector<Pos> two_segments = {
      Pos(4, 4), Pos(3, 4), Pos(3, 3), Pos(3, 2), Pos(3, 1), Pos(3, 0),
  };

  Cells cells = create_from_segments(10, one_segments, two_segments);

  GameState game_state = compute_game_logic(
      cells, 0, Direction::RIGHT, Direction::RIGHT, one_segments, two_segments);

  ASSERT_EQ(game_state, GameState::ON_GOING);

  EXPECT_EQ(cells.get(0, 0), Cell::EMPTY);
  EXPECT_EQ(cells.get(3, 0), Cell::EMPTY);

  EXPECT_EQ(cells.get(2, 4), Cell::PLAYER_ONE_HEAD);
  EXPECT_EQ(cells.get(5, 4), Cell::PLAYER_TWO_HEAD);

  EXPECT_EQ(one_segments, std::vector<Pos>({
                              Pos(2, 4),
                              Pos(1, 4),
                              Pos(0, 4),
                              Pos(0, 3),
                              Pos(0, 2),
                              Pos(0, 1),
                          }));

  EXPECT_EQ(two_segments, std::vector<Pos>({
                              Pos(5, 4),
                              Pos(4, 4),
                              Pos(3, 4),
                              Pos(3, 3),
                              Pos(3, 2),
                              Pos(3, 1),
                          }));
}

TEST(compute_game_logic, moving_into_tail) {
  std::vector<Pos> one_segments = {
      Pos(0, 0),
  };

  std::vector<Pos> two_segments = {
      Pos(0, 1),
  };

  const int CELL_SIZE = 3;
  Cells cells = create_from_segments(CELL_SIZE, one_segments, two_segments);

  GameState game_state = compute_game_logic(
      cells, 0, Direction::UP, Direction::UP, one_segments, two_segments);

  ASSERT_EQ(game_state, GameState::ON_GOING);

  EXPECT_EQ(one_segments.front(), Pos(0, 1));
  EXPECT_EQ(two_segments.front(), Pos(0, 2));

  EXPECT_EQ(cells.get(0, 1), Cell::PLAYER_ONE_HEAD);
  EXPECT_EQ(cells.get(0, 2), Cell::PLAYER_TWO_HEAD);
};

TEST(compute_game_logic, game_ending_logic_going_into_wall) {
  std::vector<Pos> one_segments = {
      Pos(0, 0),
  };

  std::vector<Pos> two_segments = {
      Pos(1, 0),
  };

  Cells cells = create_from_segments(10, one_segments, two_segments);

  GameState game_state = compute_game_logic(
      cells, 0, Direction::LEFT, Direction::UP, one_segments, two_segments);

  EXPECT_EQ(game_state, GameState::PLAYER_TWO_WON);
}

TEST(compute_game_logic, game_ending_logic_going_into_segment) {
  std::vector<Pos> one_segments = {
      Pos(0, 1),
  };

  std::vector<Pos> two_segments = {
      Pos(1, 2),
      Pos(1, 1),
      Pos(1, 0),
  };

  Cells cells = create_from_segments(10, one_segments, two_segments);

  // One is going into two segment
  GameState game_state = compute_game_logic(
      cells, 0, Direction::RIGHT, Direction::UP, one_segments, two_segments);

  EXPECT_EQ(game_state, GameState::PLAYER_TWO_WON);
}

TEST(compute_game_logic, game_ending_logic_both_dying) {
  std::vector<Pos> one_segments = {
      Pos(0, 0),
  };

  std::vector<Pos> two_segments = {
      Pos(1, 0),
  };

  Cells cells = create_from_segments(10, one_segments, two_segments);

  GameState game_state = compute_game_logic(
      cells, 0, Direction::LEFT, Direction::DOWN, one_segments, two_segments);

  EXPECT_EQ(game_state, GameState::DRAW);
}

TEST(compute_game_logic, game_ending_logic_both_going_into_the_same_cell) {
  std::vector<Pos> one_segments = {
      Pos(0, 0),
  };

  std::vector<Pos> two_segments = {
      Pos(2, 0),
  };

  Cells cells = create_from_segments(10, one_segments, two_segments);

  GameState game_state = compute_game_logic(
      cells, 0, Direction::RIGHT, Direction::LEFT, one_segments, two_segments);

  EXPECT_EQ(game_state, GameState::DRAW);
}

TEST(compute_game_logic, going_directly_into_each_other_results_in_draw) {
  std::vector<Pos> one_segments = {
      Pos(0, 0),
  };

  std::vector<Pos> two_segments = {
      Pos(1, 0),
  };

  Cells cells = create_from_segments(10, one_segments, two_segments);

  GameState game_state = compute_game_logic(
      cells, 0, Direction::RIGHT, Direction::LEFT, one_segments, two_segments);

  EXPECT_EQ(game_state, GameState::DRAW);
}

TEST(compute_game_logic, spawns_fruit_every_ten_ticks) {
  // Seed random explictly to make test reproducible
  std::srand(0);
  std::vector<Pos> one_segments = {
      Pos(0, 0),
  };

  std::vector<Pos> two_segments = {
      Pos(0, 1),
  };

  const int CELLS_SIZE = 3;
  Cells cells = create_from_segments(3, one_segments, two_segments);

  GameState game_state = compute_game_logic(
      cells, 10, Direction::UP, Direction::UP, one_segments, two_segments);

  ASSERT_EQ(game_state, GameState::ON_GOING);

  bool cells_has_fruit = false;
  for (int i = 0; i < CELLS_SIZE; i++) {
    for (int j = 0; j < CELLS_SIZE; j++) {
      if (cells.get(i, j) == Cell::FRUIT) {
        cells_has_fruit = true;
      }
    }
  }

  ASSERT_EQ(cells_has_fruit, true);

  // Make sure fruit hasn't overwritten the heads
  EXPECT_EQ(cells.get(0, 1), Cell::PLAYER_ONE_HEAD);
  EXPECT_EQ(cells.get(0, 2), Cell::PLAYER_TWO_HEAD);
}
