#include <iostream>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>

#include "core/HangmanGame.hpp"
#include "core/WordBank.hpp"
#include "core/WordRepository.hpp"
#include "core/Difficulty.hpp"
#include "core/Ruleset.hpp"

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

void test_file_word_repository_validation() {
  std::filesystem::path dir = std::filesystem::temp_directory_path() / "hangman_test_words";
  std::filesystem::create_directories(dir);

  std::filesystem::path animals = dir / "animals.txt";
  {
    std::ofstream out(animals, std::ios::binary);
    out << "CAT\r\n";
    out << "DOG\r\n";
    out << "NOT-ALPHA\r\n";
    out << "A\r\n";
    out << "MOUSE\r\n";
  }

  hangman::FileWordRepository repo(dir);
  hangman::WordValidationOptions options;
  options.minLength = 2;
  options.maxLength = 10;

  hangman::WordLoadResult loaded = repo.load(hangman::Category::Animals, options);
  expect(!loaded.words.empty(), "should load at least some valid words");

  // Ensure filtered entries are excluded and valid ones are uppercased.
  expect(std::find(loaded.words.begin(), loaded.words.end(), "CAT") != loaded.words.end(), "CAT should be present");
  expect(std::find(loaded.words.begin(), loaded.words.end(), "DOG") != loaded.words.end(), "DOG should be present");
  expect(std::find(loaded.words.begin(), loaded.words.end(), "MOUSE") != loaded.words.end(), "MOUSE should be present");
  expect(std::find(loaded.words.begin(), loaded.words.end(), "A") == loaded.words.end(), "too-short words should be excluded");

  std::error_code ec;
  std::filesystem::remove_all(dir, ec);
}

void test_difficulty_parsing_and_rules() {
  hangman::Difficulty d = hangman::Difficulty::Normal;
  expect(hangman::tryParseDifficultyId("easy", d) && d == hangman::Difficulty::Easy, "parse easy");
  expect(hangman::tryParseDifficultyId("NORMAL", d) && d == hangman::Difficulty::Normal, "parse normal");
  expect(hangman::tryParseDifficultyId("hard", d) && d == hangman::Difficulty::Hard, "parse hard");

  hangman::Ruleset easy = hangman::rulesetForDifficulty(hangman::Difficulty::Easy);
  hangman::Ruleset normal = hangman::rulesetForDifficulty(hangman::Difficulty::Normal);
  hangman::Ruleset hard = hangman::rulesetForDifficulty(hangman::Difficulty::Hard);

  expect(easy.hangman.maxAttempts > normal.hangman.maxAttempts, "easy should have more attempts than normal");
  expect(hard.hangman.maxAttempts < normal.hangman.maxAttempts, "hard should have fewer attempts than normal");
  expect(hard.scoreMultiplier >= normal.scoreMultiplier, "hard should not have lower multiplier than normal");
}

}  // namespace

int main() {
  test_masked_word();
  test_invalid_and_loss();
  test_wordbank_empty_throws();
  test_file_word_repository_validation();
  test_difficulty_parsing_and_rules();

  if (failures == 0) {
    std::cout << "All tests passed.\n";
    return 0;
  }

  std::cerr << failures << " test(s) failed.\n";
  return 1;
}
