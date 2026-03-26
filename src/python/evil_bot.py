from direction import *
from pos import Pos
from grid import Grid
from cell import Cell

# You can customize this bot to customize what my bot goes up
# against! Currently this code just simply has `EvilBot` move
# down
def evil_bot_think(grid):
  return Direction.DOWN
