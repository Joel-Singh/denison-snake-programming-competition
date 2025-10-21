#include "lib/get_commandline_args.h"
#include <gtest/gtest.h>

TEST(get_commandline_args, throws_on_too_many_args) {
  char *argv[] = {(char *)"adsf", (char *)"--evil-bot", (char *)"--yourself"};

  EXPECT_THROW(get_commandline_args(3, argv), std::invalid_argument);
}

TEST(get_commandline_args, throws_on_incorrect_option) {
  char *argv[] = {(char *)"./main", (char *)"--non-existent"};

  EXPECT_THROW(get_commandline_args(2, argv), std::invalid_argument);
}

TEST(get_commandline_args, correct_player_type_for_each_option) {
  // Default for no options is EvilBot
  char *no_options[] = {(char *)"./main"};
  EXPECT_EQ(get_commandline_args(1, no_options), PlayerType::EvilBot);

  char *evil_bot[] = {(char *)"./main", (char *)"--evil-bot"};
  EXPECT_EQ(get_commandline_args(2, evil_bot), PlayerType::EvilBot);

  char *yourself[] = {(char *)"./main", (char *)"--yourself"};
  EXPECT_EQ(get_commandline_args(2, yourself), PlayerType::Manual);

  char *my_bot[] = {(char *)"./main", (char *)"--my-bot"};
  EXPECT_EQ(get_commandline_args(2, my_bot), PlayerType::MyBot);
}
