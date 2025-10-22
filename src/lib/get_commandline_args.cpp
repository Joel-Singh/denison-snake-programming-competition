#include "lib/get_commandline_args.h"
#include <iostream>
#include <stdexcept>
#include <string>

static bool is_valid_option(char *option);

const std::string EVIL_BOT = "--evil-bot";
const std::string YOURSELF = "--yourself";
const std::string MY_BOT = "--my-bot";

Arguments get_commandline_args(int argc, char *argv[]) {
  bool options_correct = true;
  if (argc > 2) {
    throw std::invalid_argument("error: there should only be one option, "
                                "--evil-bot, --yourself, or --my-bot");
  }

  // EvilBot by default if no options
  if (argc == 1) {
    return Arguments{
        .infinite = false,
        .player_type = PlayerType::EvilBot,
    };
  }

  if (!is_valid_option(argv[1])) {
    throw std::invalid_argument(
        std::string("'") + argv[1] + "'" +
        " is invalid option, expecting --evil-bot, --yourself, or --my-bot");
  };

  if (YOURSELF == argv[1]) {
    return Arguments{
        .infinite = false,
        .player_type = PlayerType::Manual,
    };
  } else if (MY_BOT == argv[1]) {
    return Arguments{
        .infinite = false,
        .player_type = PlayerType::MyBot,
    };

  } else {
    return Arguments{
        .infinite = false,
        .player_type = PlayerType::EvilBot,
    };
  }
}

static bool is_valid_option(char *option) {
  if (EVIL_BOT == option) {
    return true;
  } else if (YOURSELF == option) {
    return true;
  } else if (MY_BOT == option) {
    return true;
  }

  return false;
}
