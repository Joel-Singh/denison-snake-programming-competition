# Game Manual

This contains more specifics of the game. If you can't find a detailing on a
rule here, you'll be able to find it in `src/lib/compute_game_logic.cpp`, which
as you can guess computes the core snake game logic. Furthermore, Joel is
always available for questions! Whether at DU Slither help sessions every
Thursday from 7 to 8 pm in Olin 311 or on the discord server.

Game constants such as board size are kept in `src/game_settings.h`, their names are used throughout this document.

## How the game logic works

This snake game operates on the notion of "game ticks". Every tick, the think
methods of each bot are called and then the resulting directions are put into
the `compute_game_logic` function which will figure out whether a snake has
won, new positions, etc. On the 100th game tick, `compute_game_logic` will return an end state (winner or draw.)

Ticks start at 0, so the first tick returned by `Grid::get_current_tick` will be 0 and the final will be `FINAL_TICK`.

## Fruits

## Board

The board is 20x20 discrete grid of squares. The origin of the board is at the bottom left and is zero indexed (i.e the bottom left cell is `(0, 0)`). Each part of each snake takes up one cell. The snakes spawn on the left and right side at the positions `(2, 10)` and `(17, 10)` precisely.

## Win Conditions
