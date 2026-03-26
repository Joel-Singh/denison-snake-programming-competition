from cell import Cell
from pos import Pos

"""
Represents cells. Has a cells property.
"""
class Cells:
  def __init__(self):
    self.cells = []

  def from_size(self, size):
    self.cells = []
    for y in range(size):
      self.cells.append([]);
      for x in range(size):
        self.cells[y].append(Cell.EMPTY);

    return self

  def from_cells_list(self, cells):
    self.cells = cells
    return self

  def height(self):
    assert len(self.cells) > 0
    return len(self.cells)

  def width(self):
    assert(len(self.cells) > 0)
    return len(self.cells[0])

  def get(self, x, y):
    if (x >= self.width() or x < 0 or y >= self.height() or y < 0):
      raise Exception("Invalid x y when calling Cells::get")

    return self.cells[y][x]

  def get_from_pos(self, pos):
    return self.get(pos.x, pos.y)

  def set(self, x, y, cell):
    if x >= self.width() or x < 0 or y >= self.height() or y < 0:
      raise Exception("Invalid x y when calling Cells.set")
    self.cells[y][x] = cell

  def set_from_pos(self, pos, cell):
    self.set(pos.x, pos.y, cell)

  def __repr__(self):
    representation = ""
    longest_cell_length = 15
    for row in reversed(self.cells):
      for cell in row:
        representation += cell.value + " " * (longest_cell_length - len(cell.value) + 1)
      representation += "\n"
    return representation

class Grid:
  """
is_player_one: Whether or not this Grid is from the perspective
of player one
current_tick: The current game time
cells: A Cells object that is read from
player_one_segments: A list of positions of first player
player_two_segments: A list of positions of the second player
"""
  def __init__(self, is_player_one, current_tick, cells,
               player_one_segments, player_two_segments):
    self.is_player_one = is_player_one
    self.current_tick = current_tick
    self.cells = cells
    self.player_one_segments = player_one_segments
    self.player_two_segments = player_two_segments


  def get_height(self):
    return self.cells.height()

  def get_width(self):
    return self.cells.width()

  def get(self, x, y):
    height = self.get_height()
    width = self.get_width()

    if x >= width or x < 0 or y >= height or y < 0:
      raise Exception("Invalid x y when calling Grid.get")

    return self.cells.get(x, y)

  def get_from_pos(self, pos):
    return self.get(pos.x, pos.y)

  def get_current_tick(self):
    return self.current_tick

  def find(self, cell):
    found = []
    for y in range(self.get_height()):
      for x in range(self.get_width()):
        if self.get(x, y) == cell:
          found.append(Pos(x, y))
    return found

  def find_fruits(self):
    return self.find(Cell.FRUIT)

  def find_self_head(self):
    if (self.is_player_one):
      return self.find(Cell.PLAYER_ONE_HEAD)[0]
    else:
      return self.find(Cell.PLAYER_TWO_HEAD)[0]

  def find_other_head(self):
    if (self.is_player_one):
      return self.find(Cell.PLAYER_TWO_HEAD)[0]
    else:
      return self.find(Cell.PLAYER_ONE_HEAD)[0]

  # Includes the head
  def find_self_positions(self):
    if self.is_player_one:
      return self.player_one_segments.copy()
    else:
      return self.player_two_segments.copy()

  # Includes the head
  def find_other_positions(self):
    if self.is_player_one:
      return self.player_two_segments.copy()
    else:
      return self.player_one_segments.copy()

  def __repr__(self):
    return self.cells.__repr__()
