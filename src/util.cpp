enum CellType {
    PLAYER_ONE,
    PLAYER_TWO,
    FRUIT,
    EMPTY
};

// Origin is bottom left. 
class Pos {
public:
    int x;
    int y;
    Pos(int x, int y) : x(x), y(y) {};
};
