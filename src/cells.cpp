#pragma once

#include <vector>
#include <cassert>
#include <stdexcept>
#include <iostream>
#include "space.h"

enum Cell {
    EMPTY,
    FRUIT,
    PLAYER_ONE,
    PLAYER_ONE_HEAD,
    PLAYER_TWO,
    PLAYER_TWO_HEAD
};

struct Cells {
    std::vector<std::vector<Cell>> cells;
    // Create Cells with size width and size height
    Cells(unsigned int size) {
        cells = std::vector<std::vector<Cell>>();

        for (int y = 0; y < size; y++) {
            cells.push_back(std::vector<Cell>());
            for (int x = 0; x < size; x++) {
                cells.at(y).push_back(Cell::EMPTY);
            }
        }
    }

    unsigned int height() const {
        assert(cells.size() > 0);
        return cells.size();
    }

    unsigned int width() const {
        assert(cells.size() > 0);
        // Assumes the the width is the same in every row 
        return cells.at(0).size();
    }

    // 0 indexed, the origin is bottom left 
    Cell get(unsigned int x, unsigned int y) const {
        if (x >= width() || x < 0 || y >= height() || y < 0) {
            throw std::logic_error("Invalid x y when calling Cells::get");
        }

        return cells.at(y).at(x);
    }

    Cell get(Pos pos) const {
        return get(pos.x, pos.y);
    }

    void set(unsigned int x, unsigned int y, Cell cell) {
        if (x >= width() || x < 0 || y >= height() || y < 0) {
            throw std::logic_error("Invalid x y when calling Cells::set");
        }
        cells.at(y).at(x) = cell;
    }

    void set(Pos pos, Cell cell) {
        set(pos.x, pos.y, cell);
    }

};
