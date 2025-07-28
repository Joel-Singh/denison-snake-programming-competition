#include "lib/input.h"

void update_input(const std::optional<sf::Event> &event, Input &input) {
  // see the sfml tutorial on key preessed and key released events:
  // https://www.sfml-dev.org/tutorials/3.0/window/events/#the-keypressed-and-keyreleased-events
  if (const auto *key_pressed = event->getIf<sf::Event::KeyPressed>()) {
    auto scancode = key_pressed->scancode;
    if (scancode == sf::Keyboard::Scan::W ||
        scancode == sf::Keyboard::Scan::Up) {
      input.was_up_pressed = true;
    }

    if (scancode == sf::Keyboard::Scan::A ||
        scancode == sf::Keyboard::Scan::Left) {
      input.was_left_pressed = true;
    }

    if (scancode == sf::Keyboard::Scan::S ||
        scancode == sf::Keyboard::Scan::Down) {
      input.was_down_pressed = true;
    }

    if (scancode == sf::Keyboard::Scan::D ||
        scancode == sf::Keyboard::Scan::Right) {
      input.was_right_pressed = true;
    }
  }
}
