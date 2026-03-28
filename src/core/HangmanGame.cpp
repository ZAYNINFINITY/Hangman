#include "core/HangmanGame.hpp"

#include <algorithm>
#include <cctype>
#include <sstream>
#include <stdexcept>

namespace hangman {

HangmanGame::HangmanGame(HangmanConfig config) : config_(config) {
  if (config_.maxAttempts <= 0) {
    throw std::invalid_argument("maxAttempts must be > 0");
  }
}

void HangmanGame::setConfig(HangmanConfig config) {
  if (config.maxAttempts <= 0) {
    throw std::invalid_argument("maxAttempts must be > 0");
  }
  config_ = config;
}

void HangmanGame::startNewRound(std::string word) {
  if (word.empty()) {
    throw std::invalid_argument("word must not be empty");
  }
  word_ = std::move(word);
  for (char& ch : word_) {
    ch = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
  }
  revealed_.assign(word_.size(), false);
  guessedLetters_.clear();
  attemptsRemaining_ = config_.maxAttempts;
}

GuessResult HangmanGame::guessLetter(char letter) {
  if (!isAlphabet(letter)) {
    return GuessResult::Invalid;
  }
  letter = normalize(letter);

  if (std::find(guessedLetters_.begin(), guessedLetters_.end(), letter) !=
      guessedLetters_.end()) {
    return GuessResult::Duplicate;
  }
  guessedLetters_.push_back(letter);

  bool correct = false;
  for (size_t i = 0; i < word_.size(); ++i) {
    if (word_[i] == letter) {
      revealed_[i] = true;
      correct = true;
    }
  }

  if (!correct) {
    attemptsRemaining_ = std::max(0, attemptsRemaining_ - 1);
    return GuessResult::Incorrect;
  }
  return GuessResult::Correct;
}

bool HangmanGame::isWon() const {
  return !word_.empty() &&
         std::all_of(revealed_.begin(), revealed_.end(), [](bool v) { return v; });
}

bool HangmanGame::isLost() const { return !isWon() && attemptsRemaining_ <= 0; }

int HangmanGame::attemptsRemaining() const { return attemptsRemaining_; }

const std::string& HangmanGame::word() const { return word_; }

std::string HangmanGame::maskedWord() const {
  std::ostringstream out;
  for (size_t i = 0; i < word_.size(); ++i) {
    if (revealed_[i]) {
      out << word_[i];
    } else {
      out << '_';
    }
    if (i + 1 < word_.size()) out << ' ';
  }
  return out.str();
}

std::string HangmanGame::guessedLettersString() const {
  std::ostringstream out;
  for (size_t i = 0; i < guessedLetters_.size(); ++i) {
    out << guessedLetters_[i];
    if (i + 1 < guessedLetters_.size()) out << ' ';
  }
  return out.str();
}

bool HangmanGame::isAlphabet(char letter) const {
  unsigned char ch = static_cast<unsigned char>(letter);
  return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

char HangmanGame::normalize(char letter) const {
  return static_cast<char>(std::toupper(static_cast<unsigned char>(letter)));
}

}  // namespace hangman
