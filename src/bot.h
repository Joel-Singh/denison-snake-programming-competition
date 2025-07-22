#pragma once

#include "space.h"
#include "grid.h"

class Bot
{
public:
    Bot(){}
    virtual Direction think(const Grid &grid) = 0;
};
