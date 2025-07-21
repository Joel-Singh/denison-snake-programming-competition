#include <gtest/gtest.h>
#include "../compute_game_logic.h"
#include "../cells.cpp"

TEST(compute_game_logic, head_movement) {
  Cells cells(10);

  cells.set(0, 0, PLAYER_ONE_HEAD);
  cells.set(0, 1, PLAYER_TWO_HEAD);

  std::vector<Pos> one_segments = { Pos(0, 0) };
  std::vector<Pos> two_segments = { Pos(0, 1) };

  GameState game_state = compute_game_logic(cells, 0, Direction::RIGHT, Direction::RIGHT, one_segments, two_segments);

  ASSERT_EQ(game_state, GameState::ON_GOING);

  EXPECT_EQ(cells.get(0, 0), Cell::EMPTY);
  EXPECT_EQ(cells.get(0, 1), Cell::EMPTY);

  EXPECT_EQ(cells.get(1, 0), Cell::PLAYER_ONE_HEAD);
  EXPECT_EQ(cells.get(1, 1), Cell::PLAYER_TWO_HEAD);

  EXPECT_EQ(one_segments.front(), Pos(1, 0));
  EXPECT_EQ(two_segments.front(), Pos(1, 1));
}

TEST(compute_game_logic, multiple_segments_straight_movement) {
  Cells cells(10);

  // A vertical snake
  cells.set(0, 5, PLAYER_ONE_HEAD);
  cells.set(0, 4, PLAYER_ONE);
  cells.set(0, 3, PLAYER_ONE);
  cells.set(0, 2, PLAYER_ONE);
  cells.set(0, 1, PLAYER_ONE);
  cells.set(0, 0, PLAYER_ONE);
  
  cells.set(1, 5, PLAYER_TWO_HEAD);
  cells.set(1, 4, PLAYER_TWO);
  cells.set(1, 3, PLAYER_TWO);
  cells.set(1, 2, PLAYER_TWO);
  cells.set(1, 1, PLAYER_TWO);
  cells.set(1, 0, PLAYER_TWO);


  std::vector<Pos> one_segments = {
    Pos(0, 5),
    Pos(0, 4),
    Pos(0, 3),
    Pos(0, 2),
    Pos(0, 1),
    Pos(0, 0),
  };

  std::vector<Pos> two_segments = {
    Pos(1, 5),
    Pos(1, 4),
    Pos(1, 3),
    Pos(1, 2),
    Pos(1, 1),
    Pos(1, 0),
  };

  GameState game_state = compute_game_logic(
    cells,
    0,
    Direction::UP,
    Direction::UP,
    one_segments,
    two_segments
  );

  ASSERT_EQ(game_state, GameState::ON_GOING);

  EXPECT_EQ(cells.get(0, 0), Cell::EMPTY);
  EXPECT_EQ(cells.get(1, 0), Cell::EMPTY);

  EXPECT_EQ(cells.get(0, 6), Cell::PLAYER_ONE_HEAD);
  EXPECT_EQ(cells.get(1, 6), Cell::PLAYER_TWO_HEAD);

  EXPECT_EQ(
    one_segments,
    std::vector<Pos>({
      Pos(0, 6), Pos(0, 5), Pos(0, 4), Pos(0, 3), Pos(0, 2), Pos(0, 1)
    })
  );

  EXPECT_EQ(
    two_segments,
    std::vector<Pos>({
      Pos(1, 6), Pos(1, 5), Pos(1, 4), Pos(1, 3), Pos(1, 2), Pos(1, 1)
    })
  );
}

TEST(compute_game_logic, multiple_segments_curved_movement) {
  Cells cells(10);

  cells.set(1, 4, PLAYER_ONE_HEAD);
  cells.set(0, 4, PLAYER_ONE);
  cells.set(0, 3, PLAYER_ONE);
  cells.set(0, 2, PLAYER_ONE);
  cells.set(0, 1, PLAYER_ONE);
  cells.set(0, 0, PLAYER_ONE);

  cells.set(4, 4, PLAYER_TWO_HEAD);
  cells.set(3, 4, PLAYER_TWO);
  cells.set(3, 3, PLAYER_TWO);
  cells.set(3, 2, PLAYER_TWO);
  cells.set(3, 1, PLAYER_TWO);
  cells.set(3, 0, PLAYER_TWO);


  std::vector<Pos> one_segments = {
    Pos(1, 4),
    Pos(0, 4),
    Pos(0, 3),
    Pos(0, 2),
    Pos(0, 1),
    Pos(0, 0),
  };

  std::vector<Pos> two_segments = {
    Pos(4, 4),
    Pos(3, 4),
    Pos(3, 3),
    Pos(3, 2),
    Pos(3, 1),
    Pos(3, 0),
  };

  GameState game_state = compute_game_logic(
    cells,
    0,
    Direction::RIGHT,
    Direction::RIGHT,
    one_segments,
    two_segments
  );

  ASSERT_EQ(game_state, GameState::ON_GOING);

  EXPECT_EQ(cells.get(0, 0), Cell::EMPTY);
  EXPECT_EQ(cells.get(3, 0), Cell::EMPTY);

  EXPECT_EQ(cells.get(2, 4), Cell::PLAYER_ONE_HEAD);
  EXPECT_EQ(cells.get(5, 4), Cell::PLAYER_TWO_HEAD);

  EXPECT_EQ(
    one_segments,
    std::vector<Pos>({
      Pos(2, 4),
      Pos(1, 4),
      Pos(0, 4),
      Pos(0, 3),
      Pos(0, 2),
      Pos(0, 1),
    })
  );

  EXPECT_EQ(
    two_segments,
    std::vector<Pos>({
      Pos(5, 4),
      Pos(4, 4),
      Pos(3, 4),
      Pos(3, 3),
      Pos(3, 2),
      Pos(3, 1),
    })
  );
}
