#include <SFML/Graphics.hpp>
#include <iostream>

void draw_grid(sf::RenderWindow &window, int grid_size, float cell_size, sf::Vector2f position);

int main()
{
    const int GRID_SIZE = 10;
    const float CELL_SIZE = 40;

    sf::RenderWindow window(sf::VideoMode({200, 200}), "SFML works!");
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                // update the view to the new size of the window
                sf::FloatRect visibleArea({0.f, 0.f}, sf::Vector2f(resized->size));
                window.setView(sf::View(visibleArea));
            }
        }

        window.clear(sf::Color::White);
        draw_grid(window, GRID_SIZE, CELL_SIZE, {0, 0});
        window.display();
    }
}

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
