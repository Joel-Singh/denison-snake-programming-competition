# Game Manual

This contains more specifics of the game. If you can't find a detailing on a
rule here, you'll be able to find it in `src/lib/compute_game_logic.cpp`, which
as you can guess computes the core snake game logic. Furthermore, Joel is
always available for questions! Whether at DU Slither help sessions every
Thursday from 7 to 8 pm in Olin 311 or on the discord server.

Game constants such as board size are kept in `src/game_settings.h`.

## Board

The board is 20x20 discrete grid of squares. The origin of the board is at the bottom left and is zero indexed (i.e the bottom left cell is `(0, 0)`). Each part of each snake takes up one cell. The snakes spawn on the left and right side at the positions `(2, 10)` and `(17, 10)` precisely.

## Win Conditions

The game and underlying `Grid` api will

Every competitor will implement 

don't use ai
