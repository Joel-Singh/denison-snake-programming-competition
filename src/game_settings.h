/// \brief The final tick that the game runs on. Will determine a winner (or
/// draw) at the end of this tick. Grid::get_current_tick will only ever be as
/// high as FINAL_TICK
const unsigned int FINAL_TICK = 100;

/// \breif the size of the square grid the game takes place upon. Also
/// obtainable with Grid::ge_height and Grid::get_width
const int CELL_SIZE = 20; // Square grid
