# Contributing

## Architecture

This is a C++ project using the [SFML](https://www.sfml-dev.org/tutorials/3.0/) library for graphics and input; CMake for building; [GoogleTest](https://github.com/google/googletest) for testing; and [Doxygen](https://doxygen.nl/) for documentation.

### The Main Program

If you open `src/main.cpp`, you'll notice that it essentially manages the window, draws the graphics, and keeps state around the the `compute_game_logic` function. As you can guess, `compute_game_logic` does all the heavy lifting for deciding how snakes move, spawning fruits, etc.

## Workflow

To contribute, a typical workflow is used: Fork, branch, and then make a pull request to the main branch. Joel will review the request, make feedback as necessary, and approve.

Make sure to install and run your code through [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html).

## Running The Project

See README.md for instructions on compiling and running.

## Tests

We use GoogleTest as our testing framework. To run tests, build the project like usual:
```
cmake --build build
```

And then run the resulting test binary:
```
./build/bin/main_tests
```

Note, tests are also run automatically on every pull request (TODO: need to set this up)

## Documentation
Currently, there is documentation written for the code used by students in the competition, but only partial documentation for internals (sorry!)

### Structure
See [Doxygen](https://doxygen.nl/), the documentation generator we used.

Here is an example of how docs are written in this project, with an explanation below:
```cpp
///
/// \brief Represents the grid of cells containing snakes and fruits. Grid is
/// used in the \ref MyBot::think function to create your bot
///
/// Also see the std library
/// [vector](https://en.cppreference.com/w/cpp/container/vector.html) that is
/// returned from multiple methods. You can think of a vector as analagous to a
/// python list.
class Grid {
public:
  ///
  /// \cond INTERNAL
  /// Hide the constructor as students will never directly use the constructor
  /// themselves
  ///
  /// \param player_one_segments,player_two_segments the ordered segments of
  /// each snake with the first element being the head.
  Grid(bool is_player_one, const Cells &cells,
       const std::vector<Pos> &player_one_segments,
       const std::vector<Pos> &player_two_segments);
  ///
  /// \endcond
  ///

  /// \brief Returns a \ref Cell at (x, y) or throws if x and y are invalid
  ///
  /// x is valid inclusively from 0 to Grid::get_height() -1 and y
  /// is valid inclusively from 0 to Grid::get_width() -1.
  Cell get(int x, int y) const;

  // ...
}
```

Documentation blocks are written in comments with three slashes.
Every element you want to document is preceded by these blocks. If we take a closer look at one of these:
```cpp
  /// \brief Returns a \ref Cell at (x, y) or throws if x and y are invalid
  ///
  /// x is valid inclusively from 0 to Grid::get_height() -1 and y
  /// is valid inclusively from 0 to Grid::get_width() -1.
  Cell get(int x, int y) const;
```

Special commands in Doxygen are prepended with a backslash. The `\brief` command and the text that follows it is the brief description of that element that will be rendered at the top. The rest of the doc block (separated with a newline), will be rendered below the brief.

Something else you may notice are doc blocks surrounded with `\cond INTERNAL` and `\endcond`. These tell Doxygen what *not* to include in the final generated documentation. You'll see these "conditionals" around items that students don't need to worry about when creating a bot.

### Building
If modifying documentation and you need to see your changes, you can build locally.

- [install Doxygen](https://doxygen.nl/manual/install.html)
- Run `doxygen`
- And then with the web browser of your choice, open up `./docs/html/index.html`
