#include "core/Difficulty.hpp"

#include <algorithm>

namespace hangman {

const char* difficultyId(Difficulty difficulty) {
  switch (difficulty) {
    case Difficulty::Easy:
      return "easy";
    case Difficulty::Normal:
      return "normal";
    case Difficulty::Hard:
      return "hard";
  }
  return "unknown";
}

std::string difficultyDisplayName(Difficulty difficulty) {
  switch (difficulty) {
    case Difficulty::Easy:
      return "Easy";
    case Difficulty::Normal:
      return "Normal";
    case Difficulty::Hard:
      return "Hard";
  }
  return "Unknown";
}

bool tryParseDifficultyId(const std::string& id, Difficulty& out) {
  std::string lowered = id;
  std::transform(lowered.begin(), lowered.end(), lowered.begin(),
                 [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

  if (lowered == "easy") {
    out = Difficulty::Easy;
    return true;
  }
  if (lowered == "normal" || lowered == "medium") {
    out = Difficulty::Normal;
    return true;
  }
  if (lowered == "hard") {
    out = Difficulty::Hard;
    return true;
  }
  return false;
}

}  // namespace hangman

