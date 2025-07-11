#include <iostream>
#include "stdexcept"
#include "space.h"

Pos::Pos(int x, int y) : x(x), y(y) {};

bool Pos::operator==(const Pos &other) const {
    return other.x == x && other.y == y;
}

std::ostream& operator<<(std::ostream& os, const Pos& pos)
{
    os << "Pos(" << pos.x << "," << pos.y << ")";
    return os;
}
