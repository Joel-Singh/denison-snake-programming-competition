#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "util.cpp"

using namespace std;

sf::Color celltype_to_color(Cell cell_type);
float calculate_cell_size(unsigned int win_height, unsigned int cells_height_count);
sf::Vector2f calculate_centered_position(sf::Vector2u win_size, sf::Vector2f board_size);

// Draws a centered grid
void draw_grid(sf::RenderWindow &window, Cells cells) {
    unsigned int cells_height_count = cells.size();
    // Assuming every row is the same size
    unsigned int cells_width_count = cells.at(0).size();

    float cell_size = calculate_cell_size(window.getSize().y, cells.size());
    sf::Vector2f centered_position = calculate_centered_position(
        window.getSize(),
        { cells_width_count * cell_size, cells_height_count * cell_size}
    );

    sf::RectangleShape cell({cell_size, cell_size});
    cell.setPosition(centered_position);

    for (int i = 0; i < cells.size(); i++) {
        // Draws from the top, so have to work backwards in the array
        for (int j = 0; j < cells.at(cells.size() - i - 1).size(); j++) {
            cell.setFillColor(celltype_to_color(cells.at(i).at(j)));
            window.draw(cell);

            sf::Vector2f next = cell.getPosition() + sf::Vector2f({cell_size, 0});
            cell.setPosition(next);
        }

        sf::Vector2f next({centered_position.x, cell.getPosition().y + cell_size});
        cell.setPosition(next);
    }
}

sf::Color celltype_to_color(Cell cell_type) {
    if (cell_type == Cell::FRUIT) {
        return sf::Color::Red;
    } else if (cell_type == Cell::EMPTY) {
        return sf::Color::Black;
    } else if (cell_type == PLAYER_ONE) {
        return sf::Color::Blue;
    } else if (cell_type == PLAYER_TWO) {
        return sf::Color::Red;
    }

    throw logic_error("Missing Cell branch in celltype_to_color!");
}

float calculate_cell_size(unsigned int win_height, unsigned int cells_height_count) {
    const float MIN_CELL_SIZE = 5;
    const float MARGIN = 200;
    float cell_size = ((float) win_height - MARGIN) / cells_height_count;

    return max(cell_size, MIN_CELL_SIZE);
}

sf::Vector2f calculate_centered_position(sf::Vector2u win_size, sf::Vector2f board_size) {
    sf::Vector2f empty_space = { win_size.x - board_size.x, win_size.y - board_size.y };
    sf::Vector2f position = { empty_space.x / 2, empty_space.y / 2 };

    return position;
}
