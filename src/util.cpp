enum CellType {
    EMPTY,
    FRUIT,
    PLAYER_ONE,
    PLAYER_TWO,
};

// Origin is bottom left. 
class Pos {
public:
    int x;
    int y;
    Pos(int x, int y) : x(x), y(y) {};
};
