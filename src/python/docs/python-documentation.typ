#import "./general-template.typ": *

#show: general.with(
  title: "DU Slither Python Documentation",
  preamble: [DU Slither Python Documentation detailing the Grid
    object given to your think function and associated
    objects.],
  class: "DU Code",
  professional: true,
)
= Introduction

Howdy! This is the documentation for the Python version of DU
Slither. To start, if you look in `src/python/my_bot.py` you'll
see this file:

```py
from src.python.direction import *
from src.python.pos import Pos
from src.python.grid import Grid
from src.python.cell import Cell

# The function you'll implement for your bot! The default code here
# simply has `MyBot` move up
#
def my_bot_think(grid):
  return Direction.UP
```

This is the primary function you'll implement. You do alllll of
your thinking in this function and at the very end, you return a
direction you wish to go to. The primary thing to understand
with this function is `grid`. `grid` is what lets you figure out
whats on the board, where the fruit are, where you are, where
your opponent is, etc. Detailed below are all the methods you
can call on `grid` in order to get information. There is another
section that details helper objects that many `grid` functions
use. Such as a `Pos` class for positions or `Direction` for
directions.

= Grid

- `grid.get_height()` returns the height of the `grid` as an
  integer.
- `grid.get_width()` returns the width of the `grid` as an
  integer.

For example:

```py
def my_bot_think(grid):
  y_position = grid.find_self_head().y
  # is it safe to move up?
  if y_position != grid.height() - 1:
    return Direction.UP # it is!
```

- `grid.get(x, y)` returns the `Cell` at the given `x` and `y`.
  $(0, 0)$ is the bottom left of the board.

- `grid.get_from_pos(pos)` returns the `Cell` at the given
  `Pos`.

For example:

```py
def my_bot_think(grid):
  self_head = grid.find_self_head()

  # Find all the cells around the head
  above = self_head.with_dir(Direction.UP)
  below = self_head.with_dir(Direction.BELOW)
  left = self_head.with_dir(Direct.LEFT)

  # Move in a direction with an empty cell
  if grid.get_from_pos(above) == Cell.EMPTY:
    return Direction.UP
  elif grid.get_from_pos(below) == Cell.EMPTY:
    return Direction.BELOW
  elif grid.get_from_pos(left) == Cell.EMPTY:
    return Direction.LEFT
  else:
    return Direction.RIGHT
```

- `grid.get_current_tick()` returns an integer that represents
  the current tick. The very final tick will be 300.

```py
def my_bot_think(grid):
  # Say, we want to program our bot to chase fruit after 250
  # ticks as the game ends at 300 ticks and the longest snake at
  # the end wins. Otherwise, chase the other snake trying to kill
  # it:

  if grid.get_current_tick() > 250:
    # Code to chase fruit...
  else:
    # Code to chase the other snake...

```

- `grid.find(cell)` returns the list of `Pos` that `cell`
  occupies.

For example:

```py
def my_bot_think(grid):
  # Find fruits
  fruits = grid.find(Cell.FRUIT)
  self_head = grid.find_self_head()

  # If there are fruit, move towards it
  if len(fruits) != 0:
    fruit = fruits[0]
    if fruit.x < self_head.x:
      return Direction.LEFT
    if fruit.x > self_head.x:
      return Direction.RIGHT
    # ... rest of the logic to move toward fruit
  else:
    return Direction.UP
```

- `grid.find_fruits()` returns the list of `Pos` that fruit
  occupy. Convenience method for `grid.find(Cell.FRUIT)`

For example:

```py
def my_bot_think(grid):
  # Find fruits
  fruits = grid.find_fruits()
  self_head = grid.find_self_head()

  # If there are fruit, move towards it
  if len(fruits) != 0:
    fruit = fruits[0]
    if fruit.x < self_head.x:
      return Direction.LEFT
    if fruit.x > self_head.x:
      return Direction.RIGHT
    # ... rest of the logic to move toward fruit
  else:
    return Direction.UP
```

- `grid.find_self_head()` returns a position of where your head
  currently is.

```py
def my_bot_think(grid):
  y_position = grid.find_self_head().y
  # is it safe to move up?
  if y_position != grid.height() - 1:
    return Direction.UP # it is!
  else:
   return Direction.DOWN
```

- `grid.find_other_head()` returns a position of where your
  opponent's head currently is.

```py
def my_bot_think(grid):
  other_head = grid.find_other_head()
  self_head = grid.find_self_head()
  # Try to move away from the opponent's head
  if other_head.x < self_head.x:
    return Direction.RIGHT
  if other_head.x > self_head.x:
    return Direction.LEFT
  if other_head.y < self_head.y:
    return Direction.UP
  return Direction.DOWN
```

- `grid.find_self_positions()` returns a list of positions of
  where your body parts are, including your head. The list is in
  order from head to tail.

- `grid.find_other_positions()` returns a list of positions of
  where the other snakes body parts are, including its head. The
  list is in order from head to tail.

```py
def my_bot_think(grid):
  # Let's say I want to chase the other snake only if I am
  # longer

  self_positions = grid.find_self_positions()
  other_positions = grid.find_other_positions()

  if len(self_positions) > len(other_positions):
    # Run the necessary code to try to chase and trap the other
    # snake
  else:
    # Run code to run away from the other snake
```


= Fun Size Helper Classes

These are all the classes that the above methods

== `Cell`

You can access one of seven cell types with the `Cell` class.

For example:
```py
if grid.get(0, 0) == Cell.EMPTY:
  print("0, 0 is empty!")

if grid.get(0, 0) == Cell.FRUIT:
  print("0, 0 is fruit!")

if grid.get(0, 0) == Cell.PLAYER_ONE:
  print("0, 0 is a player one body segment!")

if grid.get(0, 0) == Cell.PLAYER_ONE_HEAD:
  print("0, 0 is the head of player one!")

if grid.get(0, 0) == Cell.PLAYER_TWO:
  print("0, 0 is a player two body segment!")

if grid.get(0, 0) == Cell.PLAYER_TWO_HEAD:
  print("0, 0 is the head of player two!")
```

== `Pos`

`Pos` is a class representing a particular position. You can
access an `x` and `y` property upon it.

== `Direction`

`Direction` is a class representing a direction. You can access
one of four directions: `Direction.UP`, `Direction.DOWN`,
`Direction.RIGHT`, or `Direction.LEFT`.
