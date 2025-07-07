#include <SFML/Graphics.hpp>

void draw_grid(sf::RenderWindow &window, int grid_size, float cell_size, sf::Vector2f position) {
    sf::RectangleShape cell({cell_size, cell_size});
    cell.setFillColor(sf::Color::Black);
    cell.setPosition(position);

    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            window.draw(cell);
            sf::Vector2f next = cell.getPosition() + sf::Vector2f({cell_size, 0});
            cell.setPosition(next);
        }
        sf::Vector2f next({0, cell.getPosition().y + cell_size});
        cell.setPosition(next);
    }
}
