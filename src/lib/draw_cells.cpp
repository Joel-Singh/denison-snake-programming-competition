#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "cell.h"
#include "lib/cells.h"

sf::Color celltype_to_color(Cell cell_type);

float calculate_individual_cell_size(unsigned int win_height,
                                     unsigned int cells_height_count);

sf::Vector2f calculate_centered_position(sf::Vector2u win_size,
                                         sf::Vector2f board_size);

const sf::Color PLAYER_ONE_HEAD_COLOR = sf::Color(115, 45, 217);
const sf::Color PLAYER_ONE_BODY_COLOR = sf::Color(149, 117, 205);
const sf::Color PLAYER_TWO_HEAD_COLOR = sf::Color(232, 202, 0);
const sf::Color PLAYER_TWO_BODY_COLOR = sf::Color(255, 225, 26);
const sf::Color FRUIT_COLOR = sf::Color(255, 29, 35);
const sf::Color EMPTY_COLOR = sf::Color(46, 43, 41);

// Draws a centered grid
void draw_cells(sf::RenderWindow &window, const Cells &cells) {

  float cell_size =
      calculate_individual_cell_size(window.getSize().y, cells.height());

  sf::Vector2f centered_position = calculate_centered_position(
      window.getSize(),
      {cells.width() * cell_size, cells.height() * cell_size});

  sf::RectangleShape cell({cell_size, cell_size});
  cell.setPosition(centered_position);

  for (int i = cells.height() - 1; i >= 0; i--) {
    for (int j = 0; j < cells.width(); j++) {
      cell.setFillColor(celltype_to_color(cells.get(j, i)));
      window.draw(cell);

      sf::Vector2f next = cell.getPosition() + sf::Vector2f({cell_size, 0});
      cell.setPosition(next);
    }

    sf::Vector2f next({centered_position.x, cell.getPosition().y + cell_size});
    cell.setPosition(next);
  }
}

sf::Color celltype_to_color(Cell cell_type) {
  if (cell_type == Cell::FRUIT) {
    return FRUIT_COLOR;
  } else if (cell_type == Cell::EMPTY) {
    return EMPTY_COLOR;
  } else if (cell_type == Cell::PLAYER_ONE_HEAD) {
    return PLAYER_ONE_HEAD_COLOR;
  } else if (cell_type == Cell::PLAYER_ONE) {
    return PLAYER_ONE_BODY_COLOR;
  } else if (cell_type == Cell::PLAYER_TWO_HEAD) {
    return PLAYER_TWO_HEAD_COLOR;
  } else if (cell_type == Cell::PLAYER_TWO) {
    return PLAYER_TWO_BODY_COLOR;
  }

  throw std::logic_error("Missing Cell branch in celltype_to_color!");
}

float calculate_individual_cell_size(unsigned int win_height,
                                     unsigned int cells_height_count) {

  const float MIN_CELL_SIZE = 5;
  const float MARGIN = 200;

  float cell_size = ((float)win_height - MARGIN) / cells_height_count;

  return std::max(cell_size, MIN_CELL_SIZE);
}

sf::Vector2f calculate_centered_position(sf::Vector2u win_size,
                                         sf::Vector2f board_size) {

  sf::Vector2f empty_space = {win_size.x - board_size.x,
                              win_size.y - board_size.y};

  sf::Vector2f position = {empty_space.x / 2, empty_space.y / 2};

  return position;
}
