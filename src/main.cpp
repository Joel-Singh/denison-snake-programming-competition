#include "assert.h"
#include "cell.h"
#include "cells.h"
#include "compute_game_logic.h"
#include "create_from_segments.h"
#include "draw_cells.h"
#include "draw_text.h"
#include "evil_bot.h"
#include "my_bot.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>

const int CELL_SIZE = 20; // Square grid
const sf::Time GAME_TICK_TIME = sf::seconds(1);

const Pos player_one_start = Pos(2, CELL_SIZE / 2);
const Pos player_two_start = Pos(CELL_SIZE - 3, CELL_SIZE / 2);

int main() {
  std::srand(time(NULL)); // Seed rng with current time

  sf::Clock clock;

  sf::Font font;
  if (!font.openFromFile("./assets/OpenSans-Regular.ttf")) {
    std::cerr
        << "Was unable to open the font file ./assets/OpenSans-Regular.ttf"
        << std::endl;

    std::cerr << "Perhaps the working directory is incorrect?" << std::endl;
  }

  unsigned int game_ticks = 0;
  bool is_game_over = false;
  GameState game_state;

  std::vector<Pos> player_one_segments = {player_one_start};
  std::vector<Pos> player_two_segments = {player_two_start};

  Cells cells =
      create_from_segments(CELL_SIZE, player_one_segments, player_two_segments);

  MyBot player_one;
  EvilBot player_two;

  sf::RenderWindow window(sf::VideoMode({200, 200}), "Denison Snake!");
  window.setFramerateLimit(60);

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();

      if (const auto *resized = event->getIf<sf::Event::Resized>()) {
        // update the view to the new size of the window
        sf::FloatRect visibleArea({0.f, 0.f}, sf::Vector2f(resized->size));
        window.setView(sf::View(visibleArea));
      }
    }

    window.clear(sf::Color(46, 43, 41));

    if (clock.getElapsedTime() > GAME_TICK_TIME && !is_game_over) {
      clock.restart();

      Grid player_one_grid(cells, true);
      Grid player_two_grid(cells, false);

      Direction player_one_dir = player_one.think(player_one_grid);
      Direction player_two_dir = player_two.think(player_two_grid);

      game_state =
          compute_game_logic(cells, game_ticks, player_one_dir, player_two_dir,
                             player_one_segments, player_two_segments);

      if (game_state != GameState::ON_GOING) {
        is_game_over = true;
      }

      game_ticks++;
    }

    if (is_game_over) {
      if (game_state == GameState::PLAYER_ONE_WON) {
        draw_text("Player 1 Won!", window, font);
      } else if (game_state == GameState::PLAYER_TWO_WON) {
        draw_text("Player 2 Won!", window, font);
      } else if (game_state == GameState::DRAW) {
        draw_text("Draw!", window, font);
      } else if (game_state == GameState::ON_GOING) {
        throw std::logic_error(
            "`is_game_over` is true but game_state is `ON_GOING`");
      } else {
        throw std::logic_error("Missing branch for GameState");
      }
    }

    draw_cells(window, cells);

    window.display();
  }
}
