#include <algorithm>
#include <cctype>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include "core/Category.hpp"
#include "core/HangmanGame.hpp"
#include "core/WordBank.hpp"
#include "core/WordRepository.hpp"

namespace {

bool isAlphaLetter(char ch) {
  unsigned char uch = static_cast<unsigned char>(ch);
  return (uch >= 'A' && uch <= 'Z') || (uch >= 'a' && uch <= 'z');
}

char normalizeLetter(char ch) {
  return static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
}

unsigned int parseSeed(int argc, char** argv) {
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    const std::string prefix = "--seed=";
    if (arg.rfind(prefix, 0) == 0 && arg.size() > prefix.size()) {
      try {
        return static_cast<unsigned int>(std::stoul(arg.substr(prefix.size())));
      } catch (...) {
        return 0;
      }
    }
    if (arg == "--seed" && i + 1 < argc) {
      try {
        return static_cast<unsigned int>(std::stoul(argv[i + 1]));
      } catch (...) {
        return 0;
      }
    }
  }
  return static_cast<unsigned int>(std::time(nullptr));
}

bool tryParseCategoryArg(int argc, char** argv, hangman::Category& out) {
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    const std::string prefix = "--category=";
    if (arg.rfind(prefix, 0) == 0 && arg.size() > prefix.size()) {
      return hangman::tryParseCategoryId(arg.substr(prefix.size()), out);
    }
    if (arg == "--category" && i + 1 < argc) {
      return hangman::tryParseCategoryId(argv[i + 1], out);
    }
  }
  return false;
}

hangman::Category promptCategory() {
  while (true) {
    std::cout << "Choose a category:\n";
    std::cout << "  1) Animals\n";
    std::cout << "  2) Countries\n";
    std::cout << "  3) Movies\n";
    std::cout << "Enter choice (1-3): ";

    std::string line;
    if (!std::getline(std::cin >> std::ws, line)) return hangman::Category::Animals;
    if (line == "1") return hangman::Category::Animals;
    if (line == "2") return hangman::Category::Countries;
    if (line == "3") return hangman::Category::Movies;
    std::cout << "Invalid choice. Try again.\n\n";
  }
}

bool readGuess(char& outLetter) {
  std::string input;
  if (!std::getline(std::cin >> std::ws, input)) return false;
  if (input.empty()) return false;

  for (char ch : input) {
    if (!isAlphaLetter(ch)) continue;
    outLetter = normalizeLetter(ch);
    return true;
  }
  return false;
}

}  // namespace

int main(int argc, char** argv) {
  unsigned int seed = parseSeed(argc, argv);

  hangman::Category category = hangman::Category::Animals;
  const bool hasCategory = tryParseCategoryArg(argc, argv, category);
  if (!hasCategory) category = promptCategory();

  hangman::FileWordRepository repo("data/words");
  hangman::WordLoadResult loaded = repo.load(category);

  std::vector<std::string> words = std::move(loaded.words);
  if (words.empty()) {
    for (const auto& w : loaded.warnings) std::cerr << "Warning: " << w << "\n";
    std::cerr << "Falling back to built-in words.\n";
    words = hangman::WordBank::defaultWords();
  }

  hangman::HangmanGame game(hangman::HangmanConfig{10});
  game.startNewRound(hangman::WordBank::randomWord(words, seed));

  std::cout << "Welcome to Hangman!\n";
  std::cout << "Category: " << hangman::categoryDisplayName(category) << "\n";
  std::cout << "Tip: use --seed <n> and --category <animals|countries|movies>\n";

  while (!game.isWon() && !game.isLost()) {
    std::cout << "\nAttempts remaining: " << game.attemptsRemaining() << "\n";
    std::cout << "Word:   " << game.maskedWord() << "\n";
    std::cout << "Guessed:" << (game.guessedLettersString().empty() ? " (none)" : " " + game.guessedLettersString())
              << "\n";

    std::cout << "Enter a letter: ";
    char guess = '\0';
    if (!readGuess(guess)) {
      std::cout << "Invalid input. Please enter a letter (A-Z).\n";
      continue;
    }

    auto result = game.guessLetter(guess);
    if (result == hangman::GuessResult::Duplicate) {
      std::cout << "You've already guessed '" << guess << "'.\n";
    } else if (result == hangman::GuessResult::Invalid) {
      std::cout << "Invalid input. Please enter a letter (A-Z).\n";
    } else if (result == hangman::GuessResult::Incorrect) {
      std::cout << "Incorrect.\n";
    } else if (result == hangman::GuessResult::Correct) {
      std::cout << "Correct!\n";
    }
  }

  if (game.isWon()) {
    std::cout << "\nCongratulations! You guessed: " << game.word() << "\n";
  } else {
    std::cout << "\nGame over! The word was: " << game.word() << "\n";
  }

  return 0;
}

