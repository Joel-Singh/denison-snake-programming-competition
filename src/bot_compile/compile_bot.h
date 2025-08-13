#pragma once

#include "lib/bot.h"

class CompileBot : public Bot {
public:
  Direction think(const Grid &grid) const;
};
