from src.python.direction import Direction

class Pos:
  def __init__(self, x, y):
    self.x = x
    self.y = y

  def equals(self, other):
    return self.x == other.x and self.y == other.y

  def with_dir(self, direction):
    if direction == Direction.UP:
      return Pos(self.x, self.y + 1)
    elif direction == Direction.DOWN:
      return Pos(self.x, self.y - 1)
    elif direction == Direction.LEFT:
      return Pos(self.x - 1, self.y)
    elif direction == Direction.RIGHT:
      return Pos(self.x + 1, self.y)
    else:
      raise Exception("Missing branch for Direction")

  def __repr__(self):
    return f"({self.x}, {self.y})"
