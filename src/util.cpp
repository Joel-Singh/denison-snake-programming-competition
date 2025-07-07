#pragma once

#include <vector>

enum CellType {
    EMPTY,
    FRUIT,
    PLAYER_ONE,
    PLAYER_TWO,
};

using Cells = std::vector<std::vector<CellType>>;

// Origin is bottom left. 
class Pos {
public:
    int x;
    int y;
    Pos(int x, int y) : x(x), y(y) {};
};
