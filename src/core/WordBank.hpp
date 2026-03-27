#pragma once

#include <string>
#include <vector>

namespace hangman {

class WordBank {
 public:
  static std::vector<std::string> defaultWords();
  static std::string randomWord(const std::vector<std::string>& words, unsigned int seed);
};

}  // namespace hangman

