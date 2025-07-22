#include <SFML/Graphics.hpp>
#include <iostream>
#include "draw_cells.h"
#include "cells.cpp"
#include "compute_game_logic.h"
#include "evil_bot.h"
#include "my_bot.h"
#include "assert.h"
#include "create_from_segments.h"

const int CELL_SIZE = 10; // Square grid
const sf::Time GAME_TICK_TIME = sf::seconds(1);
const Pos player_one_start = Pos(0, 0);
const Pos player_two_start = Pos(0, 1);

int main()
{
    std::srand(time(NULL)); // Seed rng with current time

    sf::RenderWindow window(sf::VideoMode({200, 200}), "Denison Snake!");

    sf::Clock clock;

    unsigned int game_ticks = 0;

    std::vector<Pos> player_one_segments = { player_one_start };
    std::vector<Pos> player_two_segments = { player_two_start };

    Cells cells = create_from_segments(
        CELL_SIZE,
        player_one_segments,
        player_two_segments
    );

    MyBot player_one;
    EvilBot player_two;

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

        if (clock.getElapsedTime() > GAME_TICK_TIME) {
            clock.restart();

            Grid player_one_grid(cells, true);
            Grid player_two_grid(cells, false);

            Direction player_one_dir = player_one.think(player_one_grid);
            Direction player_two_dir = player_two.think(player_two_grid);

            GameState game_state = compute_game_logic(
                cells,
                game_ticks,
                player_one_dir,
                player_two_dir,
                player_one_segments,
                player_two_segments
            );

            assert(game_state == GameState::ON_GOING);

            game_ticks++;
        }

        draw_cells(window, cells);

        window.display();
    }
}
