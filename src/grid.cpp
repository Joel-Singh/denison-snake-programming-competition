#include "grid.h"
#include "stdexcept"

Grid::Grid(const Cells &data, bool is_player_one) : data(data), is_player_one(is_player_one) {};


Cell Grid::get(int x, int y) const {
    int height = get_height();
    int width = get_width();

    if (x >= width || x < 0 || y >= height || y < 0) {
        throw std::logic_error("Invalid x y when calling Grid::get");
    }

    return data.at(y).at(x);
}

int Grid::get_height() const {
    return data.size();
}

// Assume that there is atleast one row and that all rows are the same size
int Grid::get_width() const {
    return data.at(0).size();
}

std::vector<Pos> Grid::find_fruits() const {
    return find(Cell::FRUIT);
}

Pos Grid::find_self_head() const {
    if (is_player_one) {
        return find(Cell::PLAYER_ONE).at(0);
    } else {
        return find(Cell::PLAYER_TWO).at(0);
    }
}

Pos Grid::find_other_head() const {
    if (!is_player_one) {
        return find(Cell::PLAYER_TWO_HEAD).at(0);
    } else {
        return find(Cell::PLAYER_ONE_HEAD).at(0);
    }
}

// Includes the head
std::vector<Pos> Grid::find_self_positions() const {
    if (is_player_one) {
        std::vector<Pos> positions = find(Cell::PLAYER_ONE);
        positions.push_back(find_self_head());
        return positions;
    } else {
        std::vector<Pos> positions = find(Cell::PLAYER_TWO);
        positions.push_back(find_self_head());
        return positions;
    }
}

// Includes the head
std::vector<Pos> Grid::find_other_positions() const {
    if (!is_player_one) {
        std::vector<Pos> positions = find(Cell::PLAYER_TWO);
        positions.push_back(find_self_head());
        return positions;
    } else {
        std::vector<Pos> positions = find(Cell::PLAYER_ONE);
        positions.push_back(find_self_head());
        return positions;
    }
}

std::vector<Pos> Grid::find(Cell cell) const {
    std::vector<Pos> found = {};
    for (int y = 0; y < get_height(); y++) {
        for (int x = 0; x < get_width(); x++) {
            if (get(x, y) == cell) {
                found.push_back(Pos(x, y));
            } 
        }
    }
    return found;
}

