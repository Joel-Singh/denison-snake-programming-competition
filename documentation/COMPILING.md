# Compilation Instructions

For context, this project uses `cmake` and was created from the [sfml
template](https://github.com/SFML/cmake-sfml-project)

## Introduction

In order to build and run this repository, you'll need to install cmake, our
build system, and a C++ compiler. Additionally, these instructions include
setup for VSCode. There are instructions for most operating systems. If you
don't see your operating system or flavor of linux (Any nix users???,) you can
see Joel to help get setup.

Daily sessions to help with DU Slither are held Thursdays in Olin 311 from 7 to
8 pm. If compiling is a hurdle to participating, come get Joel! Environment
setup is the most frustrating part of programming.

## Windows

1. Install [CMake](https://cmake.org/download)

you'll specifically want to download and run the Windows x64 installer, `cmake-4.1.0-rc4-windows-x86_64.msi`.

2. Install [VSCode](https://code.visualstudio.com/download)

3. Install [the build tools for Visual Studio](https://visualstudio.microsoft.com/downloads/#remote-tools-for-visual-studio-2022) which will allow us to install the Microsoft C++ Compiler

- Go to [https://visualstudio.microsoft.com/downloads/#remote-tools-for-visual-studio-2022](https://visualstudio.microsoft.com/downloads/#remote-tools-for-visual-studio-2022)
- Scroll down to "Build Tools for Visual Studio" and download.
- Run the downloaded installer.
- If the website keeps redirecting you to bing instead of a download, see Joel.

4. Install the [Microsoft C++ compiler](https://code.visualstudio.com/docs/cpp/config-msvc) (MSVC)

- type in "Visual Studio Installer" on the search menu then run the installer
- Click "Modify" on Visual Studio Build Tools 2022
- Check "Desktop development with C++"
- Hit modify to save changes

5. Now, scroll down to the bottom of this document and follow the instructions for configuring VSCode

## MacOS

First, we need to install a cpp compiler or check if we have one.
1. Open a terminal

2. Type `g++ --version`

3. If you don't see output describing the cpp compiler you have installed, a prompt should appear to install it

4. Install [cmake](https://cmake.org/download/) for your version of MacOS

5. Now, scroll down to the bottom of this document and follow the instructions for configuring VSCode

## Linux
1. Install [cmake](https://cmake.org/download/)
2. Ensure all dependencies are installed

On Ubuntu and other Debian based distributions:
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

3. Now, scroll down to the bottom of this document and follow the instructions for configuring VSCode

## Running from the terminal

```
# Make sure these are run in the root of the project
cmake -B build # Only needs to run once
cmake --build build # The build command, the last argument specifies the build directory
./build/bin/main
```

You can pass the following flags to put `MyBot` up against different other bots: `--evil-bot` to go against the evil bot, `--my-bot` to go against itself, and `--yourself` to go against yourself with WASD controls.

## Configuring VSCode
1. Install the C++ and CMake VSCode extensions:

- [C++ extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
- [CMake extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)

2. Clone the repository

3. Configuring CMake:

note: the following is taken from an [official vscode guide.](https://code.visualstudio.com/docs/cpp/cmake-linux#_configure-hello-world)

Run each of the following commands, **after opening the project (file > open folder) in VSCode**, with the command pallete (Ctrl + Shift + P):

`CMake: Select a Kit`: scans your computer for compilers and lets you select one for use. Simply click "unspecified" and let it choose for you.

`CMake: Select variant`: lets you select the kind of build to do. Simply click Debug.

`CMake: Configure`: Takes what you selected before, and generates the necessary files in build/.

You only need to run the above once.

4. Running the project

You can now use the "Run and Debug" section on the left to run your code :-).
Simply choose what to run `MyBot` against with your operating system.

![What Run and Debug looks like](../README-assets/run-and-debug-in-vs-code.png)

p.s you have to use the "Run and Debug" section on the left, trying to run
`MyBot.cpp` directly with the run button in the top right won't work.

p.s.s `MyBot`, is the purple one

### Next Steps

After ensuring you're correctly setup, all thats left is to start writing your
bot! Your bot will be written in `src/m_bot.cpp`. You'll want to dive into [the
documentation](https://joel-singh.github.io/denison-snake-programming-competition/),
specifically the `Grid` class that you have access to within `think`. `Grid`
has a wonderful array of methods to figure out where things like fruit are on
the board.

You'll also want to take a look at [the game manual](https://joel-singh.github.io/denison-snake-programming-competition/md_documentation_2GAME__MANUAL.html), which details more specific rules.
