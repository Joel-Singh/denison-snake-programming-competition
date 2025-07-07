#include <SFML/Graphics.hpp>
#include <vector>

#include "util.cpp"

using namespace std;

const float CELL_SIZE = 40; // temporary, the cell size will be dependent
// on window size

sf::Color celltype_to_color(CellType cell_type);

void draw_grid(sf::RenderWindow &window, vector<vector<CellType>> cells) {
    sf::RectangleShape cell({CELL_SIZE, CELL_SIZE});

    for (int i = 0; i < cells.size(); i++) {
        // Draws from the top, so have to work backwards in the array
        for (int j = 0; j < cells.at(cells.size() - i - 1).size(); j++) {
            cell.setFillColor(celltype_to_color(cells.at(i).at(j)));
            window.draw(cell);

            sf::Vector2f next = cell.getPosition() + sf::Vector2f({CELL_SIZE, 0});
            cell.setPosition(next);
        }

        sf::Vector2f next({0, cell.getPosition().y + CELL_SIZE});
        cell.setPosition(next);
    }
}

sf::Color celltype_to_color(CellType cell_type) {
    if (cell_type == CellType::FRUIT) {
        return sf::Color::Red;
    } else if (cell_type == CellType::EMPTY) {
        return sf::Color::Black;
    } else if (cell_type == PLAYER_ONE) {
        return sf::Color::Blue;
    } else if (cell_type == PLAYER_TWO) {
        return sf::Color::Red;
    }

    throw logic_error("Missing CellType branch in celltype_to_color!");
}
