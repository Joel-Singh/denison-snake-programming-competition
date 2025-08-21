#include "bot_compile/compile_bot.h"
#include "direction.h"
#include <chrono>
#include <thread>

Direction CompileBot::think(const Grid &grid) const {
  std::this_thread::sleep_for(std::chrono::milliseconds(4950));
  return Direction::UP;
}
