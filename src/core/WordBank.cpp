#include "core/WordBank.hpp"

#include <random>
#include <stdexcept>

namespace hangman {

std::vector<std::string> WordBank::defaultWords() {
  return {"CAT", "DOG", "FISH", "BIRD", "COW", "MOUSE", "RAT"};
}

std::string WordBank::randomWord(const std::vector<std::string>& words, unsigned int seed) {
  if (words.empty()) {
    throw std::invalid_argument("words must not be empty");
  }
  std::mt19937 rng(seed);
  std::uniform_int_distribution<size_t> dist(0, words.size() - 1);
  return words[dist(rng)];
}

}  // namespace hangman

