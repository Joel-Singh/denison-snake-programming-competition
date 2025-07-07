#include <SFML/Graphics.hpp>
#include <iostream>
#include "draw_grid.h"
#include "util.cpp"

const int GRID_SIZE = 10; // Square grid
const sf::Time FRUIT_SPAWN_TIME = sf::seconds(2);

vector<vector<CellType>> initialize_cells();
void spawn_fruit(vector<vector<CellType>> &cells);

int main()
{
    std::srand(time(NULL)); // Seed rng with current time

    sf::RenderWindow window(sf::VideoMode({200, 200}), "SFML works!");
    sf::Clock clock;

    // The first row is on the bottom and the last row the top
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

        if (clock.getElapsedTime() > FRUIT_SPAWN_TIME) {
            clock.restart();
            spawn_fruit(cells);
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

// Spawn a fruit if there is an empty space, else do nothing
void spawn_fruit(vector<vector<CellType>> &cells) {
    bool has_empty = false;

    for (vector<CellType> row : cells) {
        for (CellType cell: row) {
            if (cell == CellType::EMPTY) {
                has_empty = true;
                break;
            }
        }
        if (has_empty) {
            break;
        }
    }

    if (!has_empty) {
        return;
    }

    sf::Vector2i random_position;
    do {
        random_position = { std::rand() % GRID_SIZE, std::rand() % GRID_SIZE };
    } while (cells.at(random_position.y).at(random_position.x) != CellType::EMPTY);

    cells.at(random_position.y).at(random_position.x) = CellType::FRUIT;
}
