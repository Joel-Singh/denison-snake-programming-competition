#pragma once

#include "bot.h"

class EvilBot : Bot {
public:
  Direction think(const Grid &grid);
};
