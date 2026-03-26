from src.python.direction import *
from src.python.pos import Pos
from src.python.grid import Grid
from src.python.cell import Cell

# You can customize this bot to customize what my bot goes up
# against! Currently this code just simply has `EvilBot` move
# down
def evil_bot_think(grid):
  return Direction.DOWN
