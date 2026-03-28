/// \brief The final tick that the game runs on. Will determine a winner (or
/// draw) at the end of this tick. Grid::get_current_tick will only ever be as
/// high as FINAL_TICK
const unsigned int FINAL_TICK = 300;

/// \brief The size of the grid.
const int GRID_SIZE = 20; // Square grid

const int FRUIT_SPAWN_INTERVAL = 5; // in ticks
