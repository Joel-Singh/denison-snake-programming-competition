# Game Manual

This contains more specifics of the game. If you can't find a detailing on a
rule here, you'll be able to find it in `src/lib/compute_game_logic.cpp`, which
as you can guess computes the core snake game logic. Furthermore, Joel is
always available for questions! Whether at DU Slither help sessions every
Thursday from 7 to 8 pm in Olin 311 or on the discord server.

Game constants such as board size are kept in `src/game_settings.h`, their names are used throughout this document.

note: You don't need to understand or read this document to program a bot! Just
do stuff with your bot and experiment. This document is for the nitty gritty
details when you need it.

## How the game logic works

This snake game operates on the notion of "game ticks". Every tick, the think
methods of each bot are called and then the resulting directions are put into
the `compute_game_logic` function which will figure out whether a snake has
won, new positions, etc. On the 100th game tick, `compute_game_logic` will return an end state (winner or draw.)

Ticks start at 0, so the first tick returned by `Grid::get_current_tick` will be 0 and the final will be `FINAL_TICK`.

## Fruits

Fruits spawn at the end of every time `FRUIT_SPAWN_INTERVAL` ticks pass, for
instance, a fruit will spawn on the `FRUIT_SPAWN_INTERVAL` tick, on the
`FRUIT_SPAWN_INTERVAL * 2` tick, etc. However, you will not be able to see this
fruit when `Grid::get_current_tick() == FRUIT_SPAWN_INTERVAL`, it will be one
after because the fruit is spawned at the end of the tick, after your think
method is called. For instance, the first fruit you'll see will be when
`Grid::get_current_tick() == (FRUIT_SPAWN_INTERVAL + 1)`. 

## Board

The board is 20x20 discrete grid of squares. The origin of the board is at the
bottom left and is zero indexed (i.e the bottom left cell is `(0, 0)`). Each
part of each snake takes up one cell. The snakes spawn on the left and right
side at the positions `(2, 10)` and `(17, 10)` precisely.

## Resource Limits

During the actual tournament, every bot will run with 1 gigahertz of CPU, 2
gigabytes of RAM, and 5 seconds of computation time. Unlike a computationally
expensive game like Chess, computing the logic for this game should not reach
anywhere near these limits unless you accidentally have an infinite loop. These
limits are for logistic purposes such as to kill when a bot enters an infinite
loop.

## Win/Loss/Draw Conditions

A bot can lose if it runs into a wall, runs into the other bot, or its think
function crashes in some way such as an exception. Note, that for this project
specfically, if a think function throws an exception or segfaults, the entire
program will crash. During the actual hosted in-person tournament, the bot will
indeed lose. 

One non-obvious endcase is If both heads run into each other, the game ends in a draw.
