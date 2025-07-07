#pragma once

#include <SFML/Graphics.hpp>
#include "util.cpp"
#include <vector>

using namespace std;

void draw_grid(sf::RenderWindow &window, vector<vector<CellType>> cells);
