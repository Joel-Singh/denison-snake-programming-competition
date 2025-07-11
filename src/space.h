#include <iostream>
#include "stdexcept"

// Origin is bottom left. 
class Pos {
public:
    int x;
    int y;
    Pos(int x, int y);
    bool operator==(const Pos &other) const;
};

std::ostream& operator<<(std::ostream& os, const Pos& pos);
