#include "my_bot.h"
#include "grid.h"
#include "pos.h"

bool is_safe_to_move(Pos pos, const Grid &grid);

/// \brief The function you'll implement for your bot! The default code here
/// simply has `MyBot` move randomly, only going into squares that are empty or
/// have fruit.
Direction MyBot::think(const Grid &grid) {
  Pos head = grid.find_self_head();

  Direction random_direction;

  // Keep choosing a random direction until its safe
  do {
    int rand = std::rand() % 4;
    if (rand == 0) {
      random_direction = Direction::UP;
    } else if (rand == 1) {
      random_direction = Direction::DOWN;
    } else if (rand == 2) {
      random_direction = Direction::LEFT;
    } else {
      random_direction = Direction::RIGHT;
    }
  } while (!is_safe_to_move(head.with_dir(random_direction), grid));

  return random_direction;
}

// Notice I can put helper methods for use in my actual think method!
bool is_safe_to_move(Pos pos, const Grid &grid) {
  // Make sure that `pos` is valid
  if (pos.x < 0 || pos.x >= grid.get_width()) {
    return false;
  }

  if (pos.y < 0 || pos.y >= grid.get_height()) {
    return false;
  }

  // Now that we know position is a valid spot on the board, we can use
  // Grid::get and check to see if its empty
  return grid.get(pos) == Cell::EMPTY || grid.get(pos) == Cell::FRUIT;
}
