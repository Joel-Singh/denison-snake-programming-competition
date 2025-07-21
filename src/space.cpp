#include <iostream>
#include "stdexcept"
#include "space.h"

// Origin is bottom left. 
Pos::Pos(int x, int y) : x(x), y(y) {};

bool Pos::operator==(const Pos &other) const {
    return other.x == x && other.y == y;
}

Pos Pos::with_dir(const Direction dir) const {
    if (dir == Direction::UP) {
        return Pos(x, y+1);
    } else if (dir == Direction::DOWN) {
        return Pos(x, y-1);
    } else if (dir == Direction::LEFT) {
        return Pos(x-1, y);
    } else if (dir == Direction::RIGHT) {
        return Pos(x+1, y);
    } else {
        throw std::logic_error("Missing branch for Direction");
    }
}

std::ostream& operator<<(std::ostream& os, const Pos& pos)
{
    os << "Pos(" << pos.x << "," << pos.y << ")";
    return os;
}
