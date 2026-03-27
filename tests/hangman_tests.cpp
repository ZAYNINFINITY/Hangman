#include <iostream>
#include <stdexcept>
#include <string>

#include "core/HangmanGame.hpp"
#include "core/WordBank.hpp"

namespace {

int failures = 0;

void expect(bool condition, const char* message) {
  if (condition) return;
  ++failures;
  std::cerr << "FAIL: " << message << "\n";
}

void test_masked_word() {
  hangman::HangmanGame game(hangman::HangmanConfig{10});
  game.startNewRound("CAT");
  expect(game.maskedWord() == "_ _ _", "masked word should start hidden");
  expect(game.guessLetter('C') == hangman::GuessResult::Correct, "C should be correct");
  expect(game.maskedWord() == "C _ _", "masked word should reveal C");
  expect(game.guessLetter('C') == hangman::GuessResult::Duplicate, "duplicate guess should be Duplicate");
}

void test_invalid_and_loss() {
  hangman::HangmanGame game(hangman::HangmanConfig{2});
  game.startNewRound("A");
  expect(game.guessLetter('1') == hangman::GuessResult::Invalid, "non-letter should be Invalid");
  expect(game.guessLetter('B') == hangman::GuessResult::Incorrect, "wrong guess should be Incorrect");
  expect(game.attemptsRemaining() == 1, "attempts should decrement");
  expect(!game.isLost(), "should not be lost yet");
  expect(game.guessLetter('C') == hangman::GuessResult::Incorrect, "wrong guess should be Incorrect");
  expect(game.isLost(), "should be lost after running out of attempts");
}

void test_wordbank_empty_throws() {
  bool threw = false;
  try {
    (void)hangman::WordBank::randomWord({}, 123u);
  } catch (const std::invalid_argument&) {
    threw = true;
  }
  expect(threw, "WordBank::randomWord should throw on empty input");
}

}  // namespace

int main() {
  test_masked_word();
  test_invalid_and_loss();
  test_wordbank_empty_throws();

  if (failures == 0) {
    std::cout << "All tests passed.\n";
    return 0;
  }

  std::cerr << failures << " test(s) failed.\n";
  return 1;
}

