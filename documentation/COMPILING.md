# Compilation Instructions

For context, this project uses `cmake` and was created from the [sfml
template](https://github.com/SFML/cmake-sfml-project)

## Windows and Visual Studio
In order to build and run this repository, you'll need to install cmake, our
build system, and a C++ compiler. If you're on Windows and use a different
IDE, feel free to reach out to Joel for help getting set up!

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

5. Now, scroll down and follow the instructions for configuring VSCode

### Configuring VSCode
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

note to self update thiis image
![What Run and Debug looks like](./README-assets/run-and-debug-in-vs-code.png)

p.s you have to use the "Run and Debug" section on the left, trying to run
`MyBot.cpp` directly with the run button in the top right won't work.

p.s.s `MyBot`, the one you're writing, is the purple one

## MacOS
<!-- add instructions to make sure g++ is installed and if not, it should prompt you to intsall it -->
1. Install [cmake](https://cmake.org/download/)
Install the dmg file for your version of macOS and double click

2. Configuring and building
```
# Make sure these are run in the root of the project
cmake -B build # Only needs to run once
cmake --build build
./build/bin/main
```

Remember, you can pass flags to `main` to control what `MyBot` goes up against.

Alternatively, if working in VSCode, you can follow the window instructions
starting from step 3 (installing the extensions) and just run the project from
VSCode


## Linux
<!-- gdb might have to also be installed -->
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

Alternatively, if working in VSCode, you can follow the window instructions
starting from step 3 (installing the extensions) and just run the project from
VSCode
