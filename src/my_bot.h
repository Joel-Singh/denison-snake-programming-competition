#pragma once

#include "lib/bot.h"

class MyBot : public Bot {
public:
  Direction think(const Grid &grid) const;
};
