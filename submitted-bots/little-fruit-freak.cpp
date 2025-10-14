#include "grid.h"
#include "my_bot.h"
#include "pos.h"

bool is_safe_to_move(Pos pos, const Grid &grid);
int get_dist(Pos a, Pos b);

/// \brief The function you'll implement for your bot! The default code here
/// simply has `MyBot` move randomly, only going into squares that are empty or
/// have fruit.
Direction MyBot::think(const Grid &grid) const {

  std::vector<Pos> fruits = grid.find_fruits();
  Pos head = grid.find_self_head();

  if (fruits.size() == 0) {
    return Direction::RIGHT;
  }

  Pos closest_fruit = fruits.at(0);

  for (Pos current_fruit : fruits) {
    int closest_fruit_distance = get_dist(head, closest_fruit);
    int current_fruit_distance = get_dist(head, current_fruit);

    if (current_fruit_distance < closest_fruit_distance) {
      closest_fruit = current_fruit;
    }
  }

  for (int i = 1; i < fruits.size(); i++) {
    while (closest_fruit.x < head.x) {
      return Direction::LEFT;
    }
    while (closest_fruit.x > head.x) {
      return Direction::RIGHT;
    }
    while (closest_fruit.y > head.y) {
      return Direction::UP;
    }
    while (closest_fruit.y < head.y) {
      return Direction::DOWN;
    }
  }
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

int get_dist(Pos a, Pos b) { return std::abs(b.x - a.x) + std::abs(b.y - a.y); }
