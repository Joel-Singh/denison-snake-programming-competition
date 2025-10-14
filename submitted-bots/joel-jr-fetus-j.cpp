#include "grid.h"
#include "my_bot.h"
#include "pos.h"
#include <algorithm>

std::vector<Direction> ALL_DIRECTIONS = {Direction::UP, Direction::DOWN,
                                         Direction::LEFT, Direction::RIGHT};

float get_distance(Pos a, Pos b) {
  int distanceX = abs(a.x - b.x);
  int distanceY = abs(a.y - b.y);
  return sqrt(pow(distanceX, 2.0) + pow(distanceY, 2.0));
}
std::vector<int> get_distance_xy(Pos a, Pos b) {
  return {b.x - a.x, b.y - a.y};
}
std::vector<Direction> find_best_directions(Pos head, Pos closestApple) {
  // given the closest apple, find y distance, x distance. if x < 0, go left, if
  // x > 0, go right, etc..
  std::vector<int> distance = get_distance_xy(head, closestApple);
  std::vector<Direction> outputDirections;
  // moving x is more of a priority than moving y
  if (std::abs(distance[0]) >= std::abs(distance[1])) {
    if (distance[0] < 0) {
      outputDirections.push_back(Direction::LEFT);
      if (distance[1] < 0) {
        outputDirections.push_back(Direction::DOWN);
        outputDirections.push_back(Direction::UP);
      } else {
        outputDirections.push_back(Direction::UP);
        outputDirections.push_back(Direction::DOWN);
      }
      outputDirections.push_back(Direction::RIGHT);
    } else {
      outputDirections.push_back(Direction::RIGHT);
      if (distance[1] < 0) {
        outputDirections.push_back(Direction::DOWN);
        outputDirections.push_back(Direction::UP);
      } else {
        outputDirections.push_back(Direction::UP);
        outputDirections.push_back(Direction::DOWN);
      }
      outputDirections.push_back(Direction::LEFT);
    }
  } else {
    if (distance[1] < 0) {
      outputDirections.push_back(Direction::DOWN);
      if (distance[0] < 0) {
        outputDirections.push_back(Direction::LEFT);
        outputDirections.push_back(Direction::RIGHT);
      } else {
        outputDirections.push_back(Direction::RIGHT);
        outputDirections.push_back(Direction::LEFT);
      }
      outputDirections.push_back(Direction::UP);

    } else {
      outputDirections.push_back(Direction::UP);
      if (distance[0] < 0) {
        outputDirections.push_back(Direction::LEFT);
        outputDirections.push_back(Direction::RIGHT);
      } else {
        outputDirections.push_back(Direction::RIGHT);
        outputDirections.push_back(Direction::LEFT);
      }
      outputDirections.push_back(Direction::DOWN);
    }
  }
  return outputDirections;
}
bool is_safe_to_move(Pos pos, const Grid &grid, int recursive, int DEPTH) {
  // Make sure that `pos` is valid
  if (pos.x < 0 || pos.x >= grid.get_width()) {
    return false;
  }

  if (pos.y < 0 || pos.y >= grid.get_height()) {
    return false;
  }

  // Now that we know position is a valid spot on the board, we can use
  // Grid::get and check to see if its empty (or, if our length is < 3, if it's
  // our own tail >:)

  int selfSnakeSize = grid.find_self_positions().size();

  if (!(grid.get(pos) == (Cell::EMPTY || grid.get(pos) == Cell::FRUIT) ||
        (selfSnakeSize < 3 && grid.get(pos) == Cell::PLAYER_ONE))) {
    return false;
  }

  // check if all directions in this
  if (recursive < DEPTH) {
    int goodDirections = 0;
    for (Direction direction : ALL_DIRECTIONS) {
      if (is_safe_to_move(pos.with_dir(direction), grid, recursive + 1,
                          DEPTH)) {
        goodDirections += 1;
      }
    }
    if (goodDirections == 0) {
      return false;
    }
  }
  // std::cout << "recursive count: " << recursive << std::endl;
  return true;
}
Pos find_closest_fruit(std::vector<Pos> fruitsList, Pos head) {

  float smallestDistance = 10;
  Pos closestFruit = fruitsList.at(0);
  // for each fruit
  for (Pos fruit : fruitsList) {
    float distance = get_distance(fruit, head);
    if (distance < smallestDistance) {
      smallestDistance = distance;
      closestFruit = fruit;
    }
  }
  return closestFruit;
}
std::vector<Pos> find_closest_fruits(std::vector<Pos> fruitsList, Pos head) {

  std::vector<Pos> orderedFruitsList = fruitsList;

  std::sort(orderedFruitsList.begin(), orderedFruitsList.end(),
            [&head](const Pos &a, const Pos &b) {
              return get_distance(a, head) < get_distance(b, head);
            });

  return orderedFruitsList;
}

/// \brief The function you'll implement for your bot! The default code here
/// simply has `MyBot` move randomly, only going into squares that are empty or
/// have fruit.
Direction MyBot::think(const Grid &grid) const {

  Pos head = grid.find_self_head(); // get position of your snake's head
  Pos oppHead =
      grid.find_other_head(); // get position of your opp's snake's head
  std::vector<Pos> apples =
      grid.find_fruits(); // get position of all of the apples on the board

  std::vector<Direction> best_directions; // we'll figure this out

  // if there's no apples on the board, go towards the origin to maximise
  // distance to next spawned apple
  if (apples.size() == 0) {
    Pos origin = Pos(10, 10);
    best_directions = find_best_directions(head, origin);
  }

  else {
    // ok, so there's at least one apple, so order them from closest to furthest
    // away
    std::vector<Pos> closest_fruits = find_closest_fruits(apples, head);

    // default the best to be the closest, just in case we don't find one ...
    Pos best_fruit = closest_fruits.at(0);

    // in order, from closest apple to furthest away...
    bool best_fruit_found = false;
    for (int i = 0; i < closest_fruits.size() & best_fruit_found == false;
         i++) {
      Pos fruit = closest_fruits.at(i);
      // if you're the closest to it, it's the best fruit
      if (get_distance(fruit, head) <= get_distance(fruit, oppHead)) {
        best_fruit_found = true;
        best_fruit = fruit;
        // std::cout << "going to fruit at " << fruit << std::endl;

      } else {
        // std::cout << "hi! you stole my fruit at " << fruit << ". going to a
        // different fruit..." << std::endl;
      }
    }
    // if there aren't any closer to you than your opponent, just default to the
    // closest to you.
    if (best_fruit_found == false) {
      best_fruit_found = true;
      // std::cout << "you're closer to every fruit than me. going to closest at
      // " << best_fruit << std::endl;
    }

    best_directions = find_best_directions(head, best_fruit);
  }

  // pick the best direction that's still safe
  for (Direction direction : best_directions) {
    if (is_safe_to_move(head.with_dir(direction), grid, 0, 3)) {
      return direction;
    }
  }

  // failsafe: give up :(
  return Direction::UP;
}
