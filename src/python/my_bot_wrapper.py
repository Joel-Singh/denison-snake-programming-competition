from src.python.readers import *
from src.python.my_bot import my_bot_think
from src.python.grid import Grid

# Expected string format of the Grid, each argument separated with a newline:
#
# a bool indicating if the bot is player one, "true"
# or "false".
#
# the current tick as an integer
#
# The size of each row on the board and all the cells from top to bottom
# separated by spaces.
#
# Player one segments as numbers separated by spaces. The first pair of
# numbers is the head. There must be an even count of numbers.
#
# Same as player one segments but represents the second player
#
# Assumes all player segments are valid (i.e they are within the given cells)
def think_wrapper(string):
  arguments = string.split("\n")
  is_player_one = read_is_player_one(arguments[0])
  current_tick = read_current_tick(arguments[1])
  cells = read_cells(arguments[2])
  player_one_segments = read_segments(arguments[3])
  player_two_segments = read_segments(arguments[4])

  return my_bot_think(Grid(is_player_one, current_tick, cells, player_one_segments, player_two_segments)).value
