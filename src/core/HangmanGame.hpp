#pragma once

#include <string>
#include <vector>

namespace hangman {

enum class GuessResult {
  Correct,
  Incorrect,
  Duplicate,
  Invalid,
};

struct HangmanConfig {
  int maxAttempts = 10;
};

class HangmanGame {
 public:
  explicit HangmanGame(HangmanConfig config);

  void setConfig(HangmanConfig config);
  void startNewRound(std::string word);

  GuessResult guessLetter(char letter);

  bool isWon() const;
  bool isLost() const;

  int attemptsRemaining() const;
  const std::string& word() const;
  std::string maskedWord() const;
  std::string guessedLettersString() const;

 private:
  bool isAlphabet(char letter) const;
  char normalize(char letter) const;

  HangmanConfig config_;
  std::string word_;
  std::vector<bool> revealed_;
  std::vector<char> guessedLetters_;
  int attemptsRemaining_ = 0;
};

}  // namespace hangman
