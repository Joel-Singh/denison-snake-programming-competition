from src.python.direction import *
from src.python.pos import Pos
from src.python.grid import Grid
from src.python.cell import Cell

# The function you'll implement for your bot! The default code here
# simply has `MyBot` stupidly chase fruit--not even checking to
# see if the cell it wants to go into is free.
#
def my_bot_think(grid):
  fruits = grid.find_fruits()
  self_head = grid.find_self_head()

  is_there_fruit = len(fruits) > 0
  if is_there_fruit:
    fruit = fruits[0]

    if fruit.x < self_head.x:
      return Direction.LEFT
    elif fruit.x > self_head.x:
      return Direction.RIGHT
    elif fruit.y < self_head.y:
      return Direction.DOWN
    elif fruit.y > self_head.y:
      return Direction.UP

  return Direction.UP
