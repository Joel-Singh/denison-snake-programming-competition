#pragma once

#include <SFML/Graphics.hpp>
#include "util.cpp"
#include <vector>

using namespace std;

void draw_cells(sf::RenderWindow &window, vector<vector<Cell>> cells);
