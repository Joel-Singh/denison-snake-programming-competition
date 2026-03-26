from src.python.cell import Cell
from src.python.grid import Cells
from src.python.pos import Pos

"""
Takes in a string representing player segments. The string are
space separated integers. Every two numbers is interpreted as a
snake position. Throws on an odd count of numbers.
"""
def read_segments(string):
  integers = string.split();
  if (len(integers) % 2) != 0:
    raise Exception("Tried reading an odd number of integers for positions!")
  segments = []
  for i in range(0, len(integers), 2):
    segments.append(Pos(integers[i], integers[i + 1]))

  return segments

def read_is_player_one(string):
  if string == "true":
    return True
  elif string == "false":
    return False
  else:
    raise Exception(f"{string} is not true or false")

def read_current_tick(string):
  return int(string)

# \brief Returns cells from a string. The string must begin with
# an integer representing the row length, and then continue with
# each Cell from left to right, top to bottom. Throws on
# malformed input. Each "cell" is a string as defined by
# "./cell.py".

def str_to_cell(string):
  if string == "EMPTY":
    return Cell.EMPTY
  elif string == "FRUIT":
    return Cell.FRUIT
  elif string == "PLAYER_ONE":
    return Cell.PLAYER_ONE
  elif string == "PLAYER_ONE_HEAD":
    return Cell.PLAYER_ONE_HEAD
  elif string == "PLAYER_TWO":
    return Cell.PLAYER_TWO
  elif string == "PLAYER_TWO_HEAD":
    return Cell.PLAYER_TWO_HEAD
  else:
    raise Exception(f"`{string}` is not a valid Cell")

def read_cells(string):
  integers = string.split()

  row_length = int(integers[0])

  cells = integers[1:]

  cells_list = []
  while len(cells) != 0:
    if len(cells) < row_length:
      raise Exception("Not enough cells for last row")

    cells_list.append([])

    for cell in cells[0:row_length]:
      cells_list[-1].append(str_to_cell(cell))

    cells = cells[row_length:]

  # Reverse because the input is given top to bottom, but the
  # first element should be the bottom.
  return Cells().from_cells_list(list(reversed(cells_list)))
