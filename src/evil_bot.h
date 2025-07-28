#pragma once

#include "lib/bot.h"

class EvilBot : public Bot {
public:
  Direction think(const Grid &grid) const;
};
