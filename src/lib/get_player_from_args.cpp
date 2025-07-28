#include "lib/get_player_from_args.h"
#include <iostream>
#include <stdexcept>
#include <string>

static bool is_valid_option(char *option);

const std::string EVIL_BOT = "--evil-bot";
const std::string YOURSELF = "--yourself";
const std::string MY_BOT = "--my-bot";

/// \brief Figures out what player 2 should be from commandline args, throwing
/// if args is wrong.
PlayerType get_player_from_args(int argc, char *argv[]) {
  bool options_correct = true;
  if (argc > 2) {
    throw std::invalid_argument("error: there should only be one option, "
                                "--evil-bot, --yourself, or --my-bot");
  }

  // EvilBot by default if no options
  if (argc == 1) {
    return PlayerType::EvilBot;
  }

  if (!is_valid_option(argv[1])) {
    throw std::invalid_argument(
        std::string("'") + argv[1] + "'" +
        " is invalid option, expecting --evil-bot, --yourself, or --my-bot");
  };

  if (YOURSELF == argv[1]) {
    return PlayerType::Manual;
  } else if (MY_BOT == argv[1]) {
    return PlayerType::MyBot;
  } else {
    return PlayerType::EvilBot;
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
