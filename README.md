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
option to the compiled binary (e.g `./build/bin/main --yourself`).

Evil bot will be chosen by default if no flags are passed.

# Compilation Instructions

For context, this project uses `cmake` and was created from the [sfml
template](https://github.com/SFML/cmake-sfml-project)

## Windows and Visual Studio
In order to build and run this repository, you'll need to install cmake, our
build system, and a C++ compiler. If you're on Windows and use a different
IDE, feel free to reach out to Joel for help getting set up!

1. Install [CMake](https://cmake.org/download)

you'll specifically want to download and run the Windows x64 installer, `cmake-4.1.0-rc4-windows-x86_64.msi`.

2. Install [Microsoft C++ compiler](https://code.visualstudio.com/docs/cpp/config-msvc) (MSVC)

You can install MSVC from the vscode installer, here are the instructions from the above link:
> open the Visual Studio Installer from the Windows Start menu and verify that
> the C++ workload is checked. If it's not installed, then check the box and
> select the Modify button in the installer.


3. Install the C++ and CMake VSCode extensions:

    - [C++ extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)

    - [CMake extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)

4. Clone the repository

Also, when running the rest of these instructions, switch to the
`writing-window-and-vscode-instructions` branch (`git switch
writing-window-and-vscode-instructions`), as it contains extra files that
configure VS Code. NOTE: switching to a specific branch won't be necessary in
the final instructions.

5. Configuring Intellisense:

note: the following is taken from an [official vscode guide.](https://code.visualstudio.com/docs/cpp/cmake-linux#_configure-hello-world)

Run each of the following commands, **after opening the project (file > open folder) in VS Code**, with the command pallete (Ctrl + Shift + P):

`CMake: Select a Kit`: scans your computer for compilers and lets you select one for use. Simply click "unspecified" and let it choose for you.

`CMake: Select variant`: lets you select the kind of build to do. Simply click Debug.

`CMake: Configure`: Takes what you selected before, and generates the necessary files in build/.

You only need to run the above once.

6. Running the project

You can now use the "Run and Debug" section on the left to run your code :-).
Simply choose what to run `MyBot` against.

![What Run and Debug looks like](./README-assets/run-and-debug-in-vs-code.png)

p.s you have to use the "Run and Debug" section on the left, trying to run
`MyBot.cpp` directly with the run button in the top right won't work.

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
```
# Make sure these are run in the root of the project
cmake -B build # Only needs to run once
cmake --build build
./build/bin/main
```

Remember, you can pass flags to `main` to control what `MyBot` goes up against.

alternatively, if working in VS Code, you can follow the window instructions
starting from step 3 (installing the extensions) and just run the project from
VS Code

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
