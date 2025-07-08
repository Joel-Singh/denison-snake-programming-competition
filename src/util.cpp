#pragma once

#include <vector>

enum Cell {
    EMPTY,
    FRUIT,
    PLAYER_ONE,
    PLAYER_ONE_HEAD,
    PLAYER_TWO,
    PLAYER_TWO_HEAD
};

// The first row is drawn on the bottom
using Cells = std::vector<std::vector<Cell>>;

