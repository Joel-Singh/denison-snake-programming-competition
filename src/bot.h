#pragma once

#include "grid.h"
#include "pos.h"

class Bot {
public:
  Bot() {}
  virtual Direction think(const Grid &grid) = 0;
};
