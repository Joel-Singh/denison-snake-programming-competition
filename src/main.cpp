#include <SFML/Graphics.hpp>
#include <iostream>
#include "draw_grid.h"

const int GRID_SIZE = 10; // Square grid

vector<vector<CellType>> initialize_cells();

int main()
{
    sf::RenderWindow window(sf::VideoMode({200, 200}), "SFML works!");
    vector<vector<CellType>> cells = initialize_cells();

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
        draw_grid(window, cells);
        window.display();
    }
}

vector<vector<CellType>> initialize_cells() {
    vector<vector<CellType>> cells;
    for (int i = 0; i < GRID_SIZE; i++) {
        cells.push_back(vector<CellType>());
        for (int j = 0; j < GRID_SIZE; j++) {
            cells.at(i).push_back(CellType::EMPTY);
        }
    }

    return cells;
}
