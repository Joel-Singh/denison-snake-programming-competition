#pragma once

#include "grid.h"
#include "pos.h"

/// \brief The class that every snake bot derives from. If you don't understand
/// what that means don't worry! Just focus implementing the logic for your bot
/// in `MyBot.cpp`.
class Bot {
public:
  Bot() {}
  /// \brief The function that determines how a bot moves by looking at the
  /// @ref Grid
  virtual Direction think(const Grid &grid) = 0;
};
