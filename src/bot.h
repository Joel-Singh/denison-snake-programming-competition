#pragma once

#include "grid.h"
#include "space.h"

class Bot {
public:
  Bot() {}
  virtual Direction think(const Grid &grid) = 0;
};
