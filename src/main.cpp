#include <SFML/Graphics.hpp>
#include <iostream>
#include "draw_cells.h"
#include "cells.cpp"

const int GRID_SIZE = 10; // Square grid
const sf::Time GAME_TICK_TIME = sf::seconds(1);

int main()
{
    std::srand(time(NULL)); // Seed rng with current time

    sf::RenderWindow window(sf::VideoMode({200, 200}), "Denison Snake!");
    sf::Clock clock;
    unsigned int game_ticks = 0;

    Cells cells(10);

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

        draw_cells(window, cells);

        window.display();
    }
}
