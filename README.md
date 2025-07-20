# DU CODE Snake Programming Competition

<!-- TODO: Add link to blog post -->

Howdy! This is the repo for Denison University's Coding Club [Snake
Programming Competition](). Participants will code a Snake bot in C++ to
face off against others. The winner will be crowned Coding Supreme.

<!-- TODO: Instead of crowning them Coding Supreme, perhaps we can get
teachers to agree to a bit of extra credit -->

# Game format

The game is very similar to classic snake except there are two of the
slithery fellows. Every timestep, the head of each snake will go up, down,
left, or right and every 10 seconds a fruit will spawn. If the head of
one snake runs into the edge, itself, or the other snake, it loses. If
the heads of the snakes run into each other, the game is considered a
draw. And of course, if a fruit is eaten, the snake gets longer.

# Writing a bot

Your bot will be implemented in `src/MyBot.cpp`, this is what will be
submitted. You may write additional helper methods and functions but they
must be contained within that single file and you may not modify the
signature of the `think` function. You can of course create more scripts
to test your bot, but in the end, `MyBot.cpp` is what will be submitted.

<!-- TODO: Add a documentation link -->

The `think` function is what will be called every time step and is what
determines what your bot does. See the [documentation]().

# Testing your bot

When running this project, there are three options for testing: 

- MyBot vs EvilBot (contained in `src/EvilBot`)
- MyBot vs yourself (controls are WASD or arrow keys)
- MyBot vs MyBot

To choose one, pass in `--evil-bot`, `--yourself`, or `--my-bot` as an
option to the compiled binary.

# Compilation Instructions

For context, this project uses `cmake` and was created from the [sfml
template](https://github.com/SFML/cmake-sfml-project)

## Windows

<!-- TODO: Create instructions for Windows -->

## MacOS

<!-- TODO: Create instructions for MacOS -->

## Linux
1. Install [cmake](https://cmake.org/download/)
2. Ensure all dependencies are installed

On Ubuntu and other Debian based distributions:
<!-- Taken from https://github.com/SFML/cmake-sfml-project -->
```
sudo apt update
sudo apt install \
    libxrandr-dev \
    libxcursor-dev \
    libxi-dev \
    libudev-dev \
    libfreetype-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev \
    libfreetype-dev
```

3. Configuring and building

Instructions for integrating directly with VSCode are provided further
down. If you wish to run the project directly on the command line:
```
# Make sure these are run in the root of the project
cmake -B build
cmake --build build
./build/bin/main
```

## Integrating with VSCode

<!-- TODO : Add instructions for how to set up passing in the relevant flags (`--evil-bot`, `--yourself`, or `--my-bot`) -->

Use the [cmake extension](https://code.visualstudio.com/docs/cpp/cmake-linux)

# Additional Rules

- You may work alone or in a group (no size limit)

# FAQ

<!-- The best format will depend on the number of entrants -->

What is the competition format?

- The actual tournament format is TBD
- We will all meet and the most interesting games / bots will be picked
out and discussed along with running the tournament for a winner.

I'm having issues compiling and running the project

- You can [create an
issue](https://github.com/Joel-Singh/denison-snake-programming-competition/issues)
with the relevant errors, contact Joel on the Coding Club discord server,
or see Joel directly at the next coding club meeting.

# Attributions

I was heavily inspired by Sebastian Lague's [Chess Challenge](https://github.com/SebLague/Chess-Challenge) and this idea for two player snake was taken from one of his [unfinished projects.](https://youtu.be/kIMHRQWorkE?t=711)
