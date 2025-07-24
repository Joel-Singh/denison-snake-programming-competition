#include "evil_bot.h"
#include "grid.h"
#include "pos.h"
#include <stdexcept>

int get_distance(Pos a, Pos b);

/// \brief This evil bot goes to the closest fruit on the board if one exists,
/// else, just go in a random direction
///
/// There are a couple of flaws with this bot. Firstly, EvilBot doesn't check to
/// see if the direction they're going in is safe (i.e isn't a segment or wall.)
/// Secondly, EvilBot never moves towards fruit diagonally, only cardinally. And
/// many more. This initial code is meant to give an example of how to use \ref
/// Grid and write a bot.
Direction EvilBot::think(const Grid &grid) {
  std::vector<Pos> fruits = grid.find_fruits();

  // if no fruits, just go in random direction
  if (grid.find_fruits().size() == 0) {
    int random = std::rand() % 4;
    if (random == 0) {
      return Direction::UP;
    } else if (random == 1) {
      return Direction::DOWN;
    } else if (random == 2) {
      return Direction::LEFT;
    } else if (random == 3) {
      return Direction::RIGHT;
    } else {
      std::cerr << "Uh oh! my code shouldn't reach here. I have a bug somewhere"
                << std::endl;
    }
  }

  Pos head = grid.find_self_head();

  // Find the closest fruit
  Pos closest_fruit = fruits.at(0);
  for (int i = 1; i < fruits.size(); i++) {
    Pos fruit = fruits.at(i);
    if (get_distance(head, fruit) < get_distance(head, closest_fruit)) {
      closest_fruit = fruit;
    }
  }

  bool is_fruit_left = (closest_fruit.x - head.x) < 0;
  bool is_fruit_right = (closest_fruit.x - head.x) > 0;
  bool is_fruit_down = (closest_fruit.y - head.y) < 0;
  bool is_fruit_up = (closest_fruit.y - head.y) > 0;

  if (is_fruit_left) {
    return Direction::LEFT;
  } else if (is_fruit_right) {
    return Direction::RIGHT;
  } else if (is_fruit_down) {
    return Direction::DOWN;
  } else if (is_fruit_up) {
    return Direction::UP;
  } else {

    // Return a default direction of UP incase our code has a bug and all the
    // bools are false
    return Direction::UP;
  }
}

// Get the distance from a to b
// Notice I can put helper methods for use in my actual think method!
int get_distance(Pos a, Pos b) {
  return std::abs((b.x - a.x)) + std::abs((b.y - a.y));
}
