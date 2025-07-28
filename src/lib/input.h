#pragma once

#include <SFML/Window.hpp>
#include <optional>

/// Represents the inputs we care about
struct Input {
  bool was_up_pressed = false;
  bool was_down_pressed = false;
  bool was_left_pressed = false;
  bool was_right_pressed = false;
};

/// Update an input from SFML events. `update_input` only ever sets an input to
/// true, it is the onus of the caller to set inputs back to false.
void update_input(const std::optional<sf::Event> &event, Input &input);
