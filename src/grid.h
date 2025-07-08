#pragma once

#include <vector>
#include <optional>
#include "util.cpp"

// Origin is bottom left. 
class Pos {
public:
    int x;
    int y;
    Pos(int x, int y) : x(x), y(y) {};
};

// Essentially a read only helper of `Cells`
class Grid {
public:
    Grid(const Cells &data, bool is_player_one);

    // Will throw an error if x and y are invalid
    Cell get(int x, int y) const;

    int get_height() const;

    int get_width() const;

    // Get the location of all fruits
    std::vector<Pos> find_fruits() const;

    // Get the position of your head
    Pos find_self_head() const;

    // Get the positions of all your parts
    std::vector<Pos> find_self_positions() const;

    // Get the position of the other snake's head
    Pos find_other_head() const;

    // Get the positions of the other snake's parts
    std::vector<Pos> find_other_positions() const;

private:
    const Cells &data;
    bool is_player_one;
    std::vector<Pos> find(Cell cell) const;
};
