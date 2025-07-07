#include <SFML/Graphics.hpp>
#include <iostream>
#include "draw_grid.h"

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
