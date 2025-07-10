#pragma once

#include <SFML/Graphics.hpp>
#include "cells.cpp"
#include <vector>

using namespace std;

void draw_cells(sf::RenderWindow &window, const Cells &cells);
