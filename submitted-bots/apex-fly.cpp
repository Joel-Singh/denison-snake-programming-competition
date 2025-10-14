#include "grid.h"
#include "my_bot.h"
#include "pos.h"

bool is_safe_to_move(Pos pos, const Grid &grid);
std::vector<Direction> getAvalDir(Pos head, const Grid &grid);
Pos getDist(Pos head, Pos object);
Pos nearstFruit(std::vector<Pos> fruits, Pos head);
bool isIn(std::vector<Direction> AvalibleDirections, Direction Dir);
Direction goRandom(std::vector<Direction> AvalibleDirections);

/// \brief The function you'll implement for your bot! The default code here
/// simply has `MyBot` move randomly, only going into squares that are empty or
/// have fruit.
Direction MyBot::think(const Grid &grid) const {
  Pos head = grid.find_self_head();
  std::vector<Pos> body = grid.find_self_positions();
  Pos evilHead = grid.find_other_head();
  std::vector<Pos> evilBody = grid.find_other_positions();
  std::vector<Pos> fruits = grid.find_fruits();

  std::vector<Direction> AvalibleDirections = getAvalDir(head, grid);

  if (AvalibleDirections.size() == 0) {
    return UP;
  } else if (AvalibleDirections.size() == 1) {
    return AvalibleDirections.front();
  }

  Direction bestDir;

  Pos evildist = getDist(head, evilHead);
  int evilTotDist = evildist.x + evildist.y;

  if (grid.get_current_tick() > 5) {
    if (fruits.size() < 1) {
      fruits.push_back(head);
    };
    Pos colsestFruit = nearstFruit(fruits, head);
    Pos fruitdist = getDist(head, colsestFruit);
    int fruitToDist = fruitdist.x + fruitdist.y;

    if ((grid.get_current_tick() < 150) && (fruitToDist < evilTotDist) &&
        (evilTotDist > 2)) {

      if (fruitdist.x > fruitdist.y) {
        if (head.x < colsestFruit.x) {
          bestDir = RIGHT;
        } else {
          bestDir = LEFT;
        }
      } else {
        if (head.y < colsestFruit.y) {
          bestDir = UP;
        } else {
          bestDir = DOWN;
        }
      }

      if (isIn(AvalibleDirections, bestDir)) {
        return bestDir;
      } else {
        return goRandom(AvalibleDirections);
      }

    } else {
      if (evildist.x > evildist.y) {
        if (head.x < evilHead.x) {
          bestDir = RIGHT;
        } else {
          bestDir = LEFT;
        }
      } else {
        if (head.y < evilHead.y) {
          bestDir = UP;
        } else {
          bestDir = DOWN;
        }
      }

      if (isIn(AvalibleDirections, bestDir)) {
        return bestDir;
      } else {
        return goRandom(AvalibleDirections);
      }
    }
  } else {
    return goRandom(AvalibleDirections);
  }

  return bestDir;
}

std::vector<Direction> getAvalDir(Pos head, const Grid &grid) {
  std::vector<Direction> AvalDir;
  if (is_safe_to_move(head.with_dir(UP), grid)) {
    auto pos = AvalDir.begin();
    Pos head2 = head;
    head2.y = head2.y + 1;
    if (is_safe_to_move(head2.with_dir(UP), grid) ||
        is_safe_to_move(head2.with_dir(DOWN), grid) ||
        is_safe_to_move(head2.with_dir(LEFT), grid) ||
        is_safe_to_move(head2.with_dir(RIGHT), grid)) {
      AvalDir.insert(pos, UP);
    }
  }
  if (is_safe_to_move(head.with_dir(DOWN), grid)) {
    auto pos = AvalDir.begin();
    Pos head2 = head;
    head2.y = head2.y - 1;
    if (is_safe_to_move(head2.with_dir(UP), grid) ||
        is_safe_to_move(head2.with_dir(DOWN), grid) ||
        is_safe_to_move(head2.with_dir(LEFT), grid) ||
        is_safe_to_move(head2.with_dir(RIGHT), grid)) {
      AvalDir.insert(pos, DOWN);
    }
  }
  if (is_safe_to_move(head.with_dir(LEFT), grid)) {
    auto pos = AvalDir.begin();
    Pos head2 = head;
    head2.x = head2.x - 1;
    if (is_safe_to_move(head2.with_dir(UP), grid) ||
        is_safe_to_move(head2.with_dir(DOWN), grid) ||
        is_safe_to_move(head2.with_dir(LEFT), grid) ||
        is_safe_to_move(head2.with_dir(RIGHT), grid)) {
      AvalDir.insert(pos, LEFT);
    }
  }
  if (is_safe_to_move(head.with_dir(RIGHT), grid)) {
    auto pos = AvalDir.begin();
    Pos head2 = head;
    head2.x = head2.x + 1;
    if (is_safe_to_move(head2.with_dir(UP), grid) ||
        is_safe_to_move(head2.with_dir(DOWN), grid) ||
        is_safe_to_move(head2.with_dir(LEFT), grid) ||
        is_safe_to_move(head2.with_dir(RIGHT), grid)) {
      AvalDir.insert(pos, RIGHT);
    }
  }
  return AvalDir;
};

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
  bool isEmpty = grid.get(pos) == Cell::EMPTY;
  bool isFruit = grid.get(pos) == Cell::FRUIT;
  return (isFruit || isEmpty);
}

Pos getDist(Pos head, Pos object) {
  Pos dist = head;
  dist.x = abs(dist.x - object.x);
  dist.y = abs(dist.y - object.y);
  return dist;
}

Pos nearstFruit(std::vector<Pos> fruits, Pos head) {
  Pos closestFruit = fruits[0];
  for (int i = 0; i < fruits.size(); i++) {
    int fruitDist =
        getDist(head, closestFruit).x + getDist(head, closestFruit).y;
    int otherDist = getDist(head, fruits[i]).x + getDist(head, fruits[i]).y;
    if (fruitDist > otherDist) {
      closestFruit = fruits[i];
    }
  }

  return closestFruit;
}

bool isIn(std::vector<Direction> AvalibleDirections, Direction Dir) {
  bool isItIn = false;
  for (int i = 0; i < AvalibleDirections.size(); i++) {
    if (Dir == AvalibleDirections[i]) {
      isItIn = true;
    }
  }
  return isItIn;
}

Direction goRandom(std::vector<Direction> AvalibleDirections) {
  int index = (std::rand() % AvalibleDirections.size());
  return AvalibleDirections[index];
}
