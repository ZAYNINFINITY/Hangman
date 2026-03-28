#pragma once

#include <string>

namespace hangman {

enum class Difficulty {
  Easy,
  Normal,
  Hard,
};

const char* difficultyId(Difficulty difficulty);
std::string difficultyDisplayName(Difficulty difficulty);
bool tryParseDifficultyId(const std::string& id, Difficulty& out);

}  // namespace hangman

