cmake_minimum_required(VERSION 3.31)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/52eb8108c5bdec04579160ae17225d66034bd723.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(
  main
  src/main.cpp

  src/space.cpp
  src/grid.cpp
  src/cells.cpp
  src/compute_game_logic.cpp
  src/my_bot.cpp
  src/evil_bot.cpp
  src/draw_cells.cpp
  src/draw_text.cpp
  src/create_from_segments.cpp
)

target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)

enable_testing()

add_executable(
  main_tests
  src/tests/main_tests.cpp

  src/space.cpp
  src/grid.cpp
  src/compute_game_logic.cpp
  src/create_from_segments.cpp
  src/cells.cpp
)
target_link_libraries(
  main_tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(main_tests)
