#include <algorithm>
#include <cctype>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include "core/Category.hpp"
#include "core/Difficulty.hpp"
#include "core/HangmanGame.hpp"
#include "core/Ruleset.hpp"
#include "core/WordBank.hpp"
#include "core/WordRepository.hpp"

namespace {

const char* versionString() {
#ifdef HANGMAN_VERSION
  return HANGMAN_VERSION;
#else
  return "dev";
#endif
}

void printHelp() {
  std::cout << "Hangman CLI\n\n";
  std::cout << "Usage:\n";
  std::cout << "  hangman_cli [--difficulty <easy|normal|hard>] [--category <animals|countries|movies>] [--seed <n>]\n\n";
  std::cout << "Options:\n";
  std::cout << "  --difficulty <id> Choose difficulty preset\n";
  std::cout << "  --category <id>   Choose word category\n";
  std::cout << "  --seed <n>        RNG seed (reproducible games)\n";
  std::cout << "  --help            Show this help\n";
  std::cout << "  --version         Show version\n";
}

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

bool tryParseDifficultyArg(int argc, char** argv, hangman::Difficulty& out) {
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    const std::string prefix = "--difficulty=";
    if (arg.rfind(prefix, 0) == 0 && arg.size() > prefix.size()) {
      return hangman::tryParseDifficultyId(arg.substr(prefix.size()), out);
    }
    if (arg == "--difficulty" && i + 1 < argc) {
      return hangman::tryParseDifficultyId(argv[i + 1], out);
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

hangman::Difficulty promptDifficulty() {
  while (true) {
    std::cout << "Choose a difficulty:\n";
    std::cout << "  1) Easy\n";
    std::cout << "  2) Normal\n";
    std::cout << "  3) Hard\n";
    std::cout << "Enter choice (1-3): ";

    std::string line;
    if (!std::getline(std::cin >> std::ws, line)) return hangman::Difficulty::Normal;
    if (line == "1") return hangman::Difficulty::Easy;
    if (line == "2") return hangman::Difficulty::Normal;
    if (line == "3") return hangman::Difficulty::Hard;
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
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "--help" || arg == "-h") {
      printHelp();
      return 0;
    }
    if (arg == "--version") {
      std::cout << versionString() << "\n";
      return 0;
    }
  }

  unsigned int seed = parseSeed(argc, argv);

  hangman::Difficulty difficulty = hangman::Difficulty::Normal;
  const bool hasDifficulty = tryParseDifficultyArg(argc, argv, difficulty);
  if (!hasDifficulty) difficulty = promptDifficulty();

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

  hangman::Ruleset rules = hangman::rulesetForDifficulty(difficulty);
  hangman::HangmanGame game(rules.hangman);
  game.startNewRound(hangman::WordBank::randomWord(words, seed));

  std::cout << "Welcome to Hangman!\n";
  std::cout << "Difficulty: " << hangman::difficultyDisplayName(difficulty) << "\n";
  std::cout << "Category: " << hangman::categoryDisplayName(category) << "\n";
  std::cout << "Tip: use --seed <n>, --category <animals|countries|movies>, --difficulty <easy|normal|hard>\n";

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
