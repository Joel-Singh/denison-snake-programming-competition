#pragma once

#include <vector>

enum Cell {
    EMPTY,
    FRUIT,
    PLAYER_ONE,
    PLAYER_TWO,
};

using Cells = std::vector<std::vector<Cell>>;

// Origin is bottom left. 
class Pos {
public:
    int x;
    int y;
    Pos(int x, int y) : x(x), y(y) {};
};
