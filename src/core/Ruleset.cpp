#include "core/Ruleset.hpp"

namespace hangman {

Ruleset rulesetForDifficulty(Difficulty difficulty) {
  Ruleset r;
  r.difficulty = difficulty;

  switch (difficulty) {
    case Difficulty::Easy:
      r.hangman.maxAttempts = 12;
      r.scoreMultiplier = 0.9;
      break;
    case Difficulty::Normal:
      r.hangman.maxAttempts = 10;
      r.scoreMultiplier = 1.0;
      break;
    case Difficulty::Hard:
      r.hangman.maxAttempts = 7;
      r.scoreMultiplier = 1.25;
      break;
  }

  return r;
}

}  // namespace hangman

