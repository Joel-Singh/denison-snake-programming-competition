#include "my_bot.h"
#include "grid.h"
#include "pos.h"

/// \brief The function you'll implement for your bot! The default code here
/// simply has `MyBot` move up and down, trying not to move into the top or
/// bottom walls.
Direction MyBot::think(const Grid &grid) {
  int rand = std::rand() % 2;
  if (rand == 0) {
    Pos self = grid.find_self_head();

    // Move up if we aren't at the top
    if (self.y != (grid.get_height() - 1)) {
      return Direction::UP;
    } else {
      return Direction::DOWN;
    }
  } else {
    Pos self = grid.find_self_head();

    // Move down if we aren't at the bottom
    if (self.y != 0) {
      return Direction::DOWN;
    } else {
      return Direction::UP;
    }
  }
}
