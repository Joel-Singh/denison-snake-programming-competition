#include <chrono>

/// \brief The final tick that the game runs on. Will determine a winner (or
/// draw) at the end of this tick. Grid::get_current_tick will only ever be as
/// high as FINAL_TICK
const unsigned int FINAL_TICK = 100;

/// \brief the size of the square grid the game takes place upon. Also
/// obtainable with Grid::ge_height and Grid::get_width
const int CELL_SIZE = 20; // Square grid

/// \brief the limit of ram in megabytes bots in the tournament are run at.
const int RAM_LIMIT = 1000;

/// \brief the limit of CPU in megahertz bots in the tournament are run at.
const int CPU_LIMIT = 1000;

/// \brief the time limit bots in the tournamnet have.
const std::chrono::duration TIME_LIMIT = std::chrono::milliseconds(5000);
