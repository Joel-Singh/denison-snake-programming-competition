#include "lib/get_commandline_args.h"
#include <gtest/gtest.h>

TEST(get_commandline_args, throws_on_specifying_multiple_player_types) {
  char *argv1[] = {(char *)"./main", (char *)"--evil-bot",
                   (char *)"--yourself"};
  EXPECT_THROW(get_commandline_args(3, argv1), std::invalid_argument);

  char *argv2[] = {(char *)"./main", (char *)"--evil-bot", (char *)"--my-bot"};
  EXPECT_THROW(get_commandline_args(3, argv2), std::invalid_argument);

  char *argv3[] = {(char *)"./main", (char *)"--yourself",
                   (char *)"--evil_bot"};
  EXPECT_THROW(get_commandline_args(3, argv3), std::invalid_argument);

  char *argv4[] = {(char *)"./main", (char *)"--yourself", (char *)"--my-bot"};
  EXPECT_THROW(get_commandline_args(3, argv4), std::invalid_argument);

  char *argv5[] = {(char *)"./main", (char *)"--my-bot", (char *)"--evil-bot"};
  EXPECT_THROW(get_commandline_args(3, argv5), std::invalid_argument);

  char *argv6[] = {(char *)"./main", (char *)"--my-bot", (char *)"--evil-bot",
                   (char *)"--yourself"};
  EXPECT_THROW(get_commandline_args(4, argv6), std::invalid_argument);

  char *argv7[] = {(char *)"./main", (char *)"--evil-bot", (char *)"--my-bot",
                   (char *)"--yourself"};
  EXPECT_THROW(get_commandline_args(4, argv7), std::invalid_argument);
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
