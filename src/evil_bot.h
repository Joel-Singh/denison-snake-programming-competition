#pragma once

#include "lib/bot.h"

class EvilBot : Bot {
public:
  Direction think(const Grid &grid);
};
