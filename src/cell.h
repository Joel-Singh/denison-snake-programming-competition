///
/// \file

#pragma once

/// \enum Cell
/// \brief Represents every cell on a [Grid](\ref Grid). \ref Cell is returned
/// by [Grid](\ref Grid)::get.
enum Cell {
  EMPTY,
  FRUIT,
  PLAYER_ONE,
  PLAYER_ONE_HEAD,
  PLAYER_TWO,
  PLAYER_TWO_HEAD
};
