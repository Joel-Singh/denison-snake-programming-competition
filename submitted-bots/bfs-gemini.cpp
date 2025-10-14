#include "grid.h"
#include "my_bot.h"
#include "pos.h"
#include <cmath>
#include <map>
#include <queue>
#include <stack>
#include <utility>

/*

Gemini Snake :):<

He will try to get in front of the other snake to kill it, but only if he is
significantly longer than the opponent

*/

namespace {
const int MIN_SIZE = 12; // Required size to start hunting
const int LEAD_DIST = 2; // Distance ahead of target to aim for

const std::vector<Direction> Directions = {Direction::UP, Direction::RIGHT,
                                           Direction::DOWN, Direction::LEFT};

Pos lastPos = Pos(0, 0);

bool is_safe_to_move(Pos pos, const Grid &grid) {
  // Make sure that `pos` is valid
  if (pos.x < 0 || pos.x >= grid.get_width()) {
    return false;
  }

  if (pos.y < 0 || pos.y >= grid.get_height()) {
    return false;
  }

  return grid.get(pos) == Cell::EMPTY || grid.get(pos) == Cell::FRUIT;
}

std::pair<int, int> pair(int x, int y) { return std::make_pair(x, y); }

std::pair<int, int> pair(Pos pos) { return pair(pos.x, pos.y); }

std::map<std::pair<int, int>, int> getDistances(Pos start, const Grid &grid) {
  std::queue<Pos> toVisit; // Pos that still need to be visited, sorted by
                           // distance from head

  std::map<std::pair<int, int>, int> distances;

  toVisit.push(start); // Start with the head node
  // Set up initial distances for all values except head as 999
  for (int x = 0; x < grid.get_width(); x++) {
    for (int y = 0; y < grid.get_height(); y++) {
      distances[pair(x, y)] = 999;
    }
  }
  distances[pair(start)] = 0;

  while (!toVisit.empty()) { // While we haven't visited every possible
                             // position, keep checking them all
    Pos currentPos = toVisit.front();
    toVisit.pop();
    for (Direction d : Directions) {
      Pos nextPos = currentPos.with_dir(d);
      int newCost = distances[pair(currentPos)] + 1;
      if (is_safe_to_move(nextPos, grid) &&
          distances[pair(nextPos)] > newCost) {
        toVisit.push(nextPos);
        distances[pair(nextPos)] = newCost;
      }
    }
  }
  return distances;
}

std::stack<Pos> pathfind(std::map<std::pair<int, int>, int> &distances,
                         Pos start, Pos goal, const Grid &grid) {
  std::stack<Pos> path;
  Pos currentPos = goal;
  while (currentPos.x != start.x || currentPos.y != start.y) {
    path.push(currentPos);
    int currentCost = 999;
    Pos currentBestPos = Pos(0, 0);
    for (Direction d : Directions) {
      Pos nextPos = currentPos.with_dir(d);
      if (distances[pair(nextPos)] < currentCost &&
          (is_safe_to_move(nextPos, grid) ||
           (nextPos.x == start.x && nextPos.y == start.y))) {
        currentCost = distances[pair(nextPos)];
        currentBestPos = nextPos;
      }
    }
    if (currentBestPos.x == 0 && currentBestPos.y == 0)
      break;
    currentPos = currentBestPos;
  }
  return path;
}
} // namespace

Direction MyBot::think(const Grid &grid) const {
  std::map<std::pair<int, int>, int> distances;
  std::stack<Pos> path;

  Pos head = grid.find_self_head(); // Snake head
  Pos goal = Pos(0, 0);

  distances = getDistances(
      head, grid); // Minimum distance from snake head to each possible Pos

  if ((grid.find_self_positions().size() <
       grid.find_other_positions().size() +
           2)) { // Go for fruits until big enough to hunt
    int fruitDist = 999;
    for (Pos fruitPos :
         grid.find_fruits()) { // Find the closest fruit and set it as the goal
                               // (defaults to 0, 0 if no fruit)
      int newDist = distances[pair(fruitPos)];
      if (newDist < fruitDist) {
        fruitDist = newDist;
        goal = fruitPos;
      }
    }
    path = pathfind(distances, head, goal, grid);
  } else { // Try to kill opponent by intercepting them
    Pos oppHead = grid.find_other_head();
    auto oppDistances = getDistances(oppHead, grid);
    int fruitDist = 999;
    for (Pos fruitPos : grid.find_fruits()) { // Guess where opponent is going
      int newDist = oppDistances[pair(fruitPos)];
      if (newDist < fruitDist) {
        fruitDist = newDist;
        goal = fruitPos;
      }
    }
    auto oppPath = pathfind(oppDistances, oppHead, goal, grid);
    if (oppPath.size() > LEAD_DIST) {
      for (int i = 0; i < LEAD_DIST - 1; i++) {
        oppPath.pop();
      }

      if (pair(lastPos) ==
          pair(oppPath.top())) { // If opponent is still on same path as before
                                 // & we can cut them off, do so
        path = pathfind(distances, head, lastPos, grid);
      } else {
        oppPath.pop();
        path = pathfind(distances, head, oppPath.top(), grid);
        lastPos = oppPath.top();
      }
    } else {
      int fruitDist = 999;
      for (Pos fruitPos :
           grid.find_fruits()) { // Go to nearest fruit as fallback
        int newDist = oppDistances[pair(fruitPos)];
        if (newDist < fruitDist) {
          fruitDist = newDist;
          goal = fruitPos;
        }
      }
      path = pathfind(distances, head, goal, grid);
    }
  }

  if (distances[pair(goal)] == 999) { // Fallback if goal is unreachable
    std::cout << "Goal unreachable!" << std::endl;
    for (Direction d : Directions) {
      Pos next = head.with_dir(d);
      if (is_safe_to_move(next, grid))
        return d;
    }
    return Direction::UP; // Default if trapped
  }

  // path now contains a stack of every position in the best path from the head
  // to the goal We just need to return the direction from the head to the first
  // Pos in the path
  Pos first = path.empty() ? Pos(0, 0) : path.top();
  if (head.x < first.x &&
      is_safe_to_move(
          head.with_dir(Direction::RIGHT),
          grid)) { // Head is to the left of first Pos, so return RIGHT
    return Direction::RIGHT;
  } else if (head.y < first.y &&
             is_safe_to_move(head.with_dir(Direction::UP),
                             grid)) { // Head is below first Pos, so return UP
    return Direction::UP;
  } else if (head.x > first.x &&
             is_safe_to_move(
                 head.with_dir(Direction::LEFT),
                 grid)) { // Head is to the right of first Pos, so return LEFT
    return Direction::LEFT;
  } else if (head.y > first.y &&
             is_safe_to_move(head.with_dir(Direction::DOWN),
                             grid)) { // Head is above first Pos (and other
                                      // default), so return DOWN
    return Direction::DOWN;
  } else {
    for (Direction d :
         Directions) { // If desired path is unsafe, go through all the
                       // directions until you find a safe one
      if (is_safe_to_move(head.with_dir(d), grid)) {
        return d;
      }
    }
    return Direction::UP; // If nothing is safe, just go up and die
  }
}
