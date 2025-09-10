cmake_minimum_required(VERSION 3.31)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

INCLUDE_DIRECTORIES(src)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(
  main
  src/lib/main.cpp

  src/pos.cpp
  src/grid.cpp
  src/lib/cells.cpp
  src/lib/compute_game_logic.cpp
  src/my_bot.cpp
  src/evil_bot.cpp
  src/lib/draw_cells.cpp
  src/lib/draw_text.cpp
  src/lib/input.cpp
  src/lib/create_from_segments.cpp
  src/lib/get_player_from_args.cpp
)

target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)
