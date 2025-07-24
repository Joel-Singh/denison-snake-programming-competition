#include <SFML/Graphics.hpp>

void draw_text(sf::String str, sf::RenderWindow &window, sf::Font font) {
  const float MARGIN_TOP = 15;

  sf::Text text(font);

  text.setString(str);

  float window_width = window.getSize().x;
  float text_width = text.getLocalBounds().size.x;

  text.setPosition({(window_width / 2.f) - text_width / 2.f, MARGIN_TOP});

  window.draw(text);
}
