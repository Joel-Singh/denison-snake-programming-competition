#include "assert.h"
#include "cell.h"
#include "evil_bot.h"
#include "lib/cells.h"
#include "lib/compute_game_logic.h"
#include "lib/create_from_segments.h"
#include "lib/draw_cells.h"
#include "lib/draw_text.h"
#include "lib/input.h"
#include "my_bot.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>

const int CELL_SIZE = 20; // Square grid
const sf::Time GAME_TICK_TIME = sf::seconds(0.2);
const sf::Color BACKGROUND_COLOR = sf::Color::Black;

const Pos player_one_start = Pos(2, CELL_SIZE / 2);
const Pos player_two_start = Pos(CELL_SIZE - 3, CELL_SIZE / 2);

GameState run_two_bot_game(Cells &cells, std::vector<Pos> &player_one_segments,
                           std::vector<Pos> &player_two_segments,
                           const Bot &player_one, const Bot &player_two,
                           const unsigned int game_ticks);

int main() {
  std::srand(time(NULL)); // Seed rng with current time

  sf::Font font;
  if (!font.openFromFile("./assets/OpenSans-Regular.ttf")) {
    std::cerr
        << "Was unable to open the font file ./assets/OpenSans-Regular.ttf"
        << std::endl;

    std::cerr << "Perhaps the working directory is incorrect?" << std::endl;

    return 1;
  }

  sf::RenderWindow window(sf::VideoMode({200, 200}), "Denison Snake!");
  window.setFramerateLimit(60);

  // Create all of our game data
  sf::Clock clock;
  Input input;

  GameState game_state = GameState::ON_GOING;
  unsigned int game_ticks = 0;

  MyBot player_one;
  std::vector<Pos> player_one_segments = {player_one_start};

  EvilBot player_two;
  std::vector<Pos> player_two_segments = {player_two_start};

  Cells cells =
      create_from_segments(CELL_SIZE, player_one_segments, player_two_segments);

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>())
        window.close();

      if (const auto *resized = event->getIf<sf::Event::Resized>()) {
        // update the view to the new size of the window
        sf::FloatRect visibleArea({0.f, 0.f}, sf::Vector2f(resized->size));
        window.setView(sf::View(visibleArea));
      }

      update_input(event, input);
    }

    window.clear(BACKGROUND_COLOR);

    if (game_state == GameState::ON_GOING) {
      if (clock.getElapsedTime() > GAME_TICK_TIME) {
        clock.restart();

        game_state =
            run_two_bot_game(cells, player_one_segments, player_two_segments,
                             player_one, player_two, game_ticks);

        game_ticks++;
      }
    } else {
      if (game_state == GameState::PLAYER_ONE_WON) {
        draw_text("Player 1 Won!", window, font);
      } else if (game_state == GameState::PLAYER_TWO_WON) {
        draw_text("Player 2 Won!", window, font);
      } else if (game_state == GameState::DRAW) {
        draw_text("Draw!", window, font);
      }
    }

    draw_cells(window, cells);
    window.display();
  }
}

GameState run_two_bot_game(Cells &cells, std::vector<Pos> &player_one_segments,
                           std::vector<Pos> &player_two_segments,
                           const Bot &player_one, const Bot &player_two,
                           const unsigned int game_ticks) {

  Grid player_one_grid(true, cells, player_one_segments, player_two_segments);
  Grid player_two_grid(false, cells, player_one_segments, player_two_segments);

  Direction player_one_dir = player_one.think(player_one_grid);
  Direction player_two_dir = player_two.think(player_two_grid);

  GameState game_state =
      compute_game_logic(cells, game_ticks, player_one_dir, player_two_dir,
                         player_one_segments, player_two_segments);

  return game_state;
}

GameState run_game_with_manual(Cells &cells,
                               std::vector<Pos> &player_one_segments,
                               std::vector<Pos> &player_two_segments,
                               const Bot &player_one,
                               const Direction manual_player_dir,
                               unsigned int game_ticks) {
  Grid player_one_grid(true, cells, player_one_segments, player_two_segments);

  Direction player_one_dir = player_one.think(player_one_grid);

  GameState game_state =
      compute_game_logic(cells, game_ticks, player_one_dir, manual_player_dir,
                         player_one_segments, player_two_segments);

  return game_state;
}
