#include "lib/get_player_two_from_args.h"
#include <gtest/gtest.h>

TEST(get_player_2_from_commandline_args, throws_on_too_many_args) {
  char *argv[] = {(char *)"adsf", (char *)"--evil-bot", (char *)"--yourself"};

  EXPECT_THROW(get_player_2_from_commandline_args(3, argv),
               std::invalid_argument);
}

TEST(get_player_2_from_commandline_args, throws_on_incorrect_option) {
  char *argv[] = {(char *)"./main", (char *)"--non-existent"};

  EXPECT_THROW(get_player_2_from_commandline_args(2, argv),
               std::invalid_argument);
}

TEST(get_player_2_from_commandline_args, correct_player_type_for_each_option) {
  // Default for no options is EvilBot
  char *no_options[] = {(char *)"./main"};
  EXPECT_EQ(get_player_2_from_commandline_args(1, no_options),
            PlayerTwo::EvilBot);

  char *evil_bot[] = {(char *)"./main", (char *)"--evil-bot"};
  EXPECT_EQ(get_player_2_from_commandline_args(2, evil_bot),
            PlayerTwo::EvilBot);

  char *yourself[] = {(char *)"./main", (char *)"--yourself"};
  EXPECT_EQ(get_player_2_from_commandline_args(2, yourself), PlayerTwo::Manual);

  char *my_bot[] = {(char *)"./main", (char *)"--my-bot"};
  EXPECT_EQ(get_player_2_from_commandline_args(2, my_bot), PlayerTwo::MyBot);
}
