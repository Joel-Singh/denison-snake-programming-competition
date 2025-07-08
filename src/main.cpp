#include <SFML/Graphics.hpp>
#include <iostream>
#include "draw_cells.h"
#include "util.cpp"

const int GRID_SIZE = 10; // Square grid
const sf::Time GAME_TICK_TIME = sf::seconds(1);

Cells initialize_cells();
void spawn_fruit(Cells &cells);

int main()
{
    std::srand(time(NULL)); // Seed rng with current time

    sf::RenderWindow window(sf::VideoMode({200, 200}), "SFML works!");
    sf::Clock clock;
    unsigned int game_ticks = 0;

    // The first row is on the bottom and the last row the top
    Cells cells = initialize_cells(); 

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

        if (clock.getElapsedTime() > GAME_TICK_TIME) {
            game_ticks++;
            clock.restart();
            if (game_ticks % 2 == 0) {
                spawn_fruit(cells);
            }
        }

        window.clear(sf::Color::White);
        draw_cells(window, cells);
        window.display();
    }
}

Cells initialize_cells() {
    Cells cells;
    for (int i = 0; i < GRID_SIZE; i++) {
        cells.push_back(vector<Cell>());
        for (int j = 0; j < GRID_SIZE; j++) {
            cells.at(i).push_back(Cell::EMPTY);
        }
    }

    return cells;
}

// Spawn a fruit if there is an empty space, else do nothing
void spawn_fruit(Cells &cells) {
    bool has_empty = false;

    for (vector<Cell> row : cells) {
        for (Cell cell: row) {
            if (cell == Cell::EMPTY) {
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
    } while (cells.at(random_position.y).at(random_position.x) != Cell::EMPTY);

    cells.at(random_position.y).at(random_position.x) = Cell::FRUIT;
}
