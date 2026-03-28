#pragma once

#include "core/Difficulty.hpp"
#include "core/HangmanGame.hpp"

namespace hangman {

struct Ruleset {
  Difficulty difficulty = Difficulty::Normal;
  HangmanConfig hangman;
  double scoreMultiplier = 1.0;
};

Ruleset rulesetForDifficulty(Difficulty difficulty);

}  // namespace hangman

