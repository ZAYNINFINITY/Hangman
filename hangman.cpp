
#include <algorithm>
#include <cctype>
#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <vector>

namespace {

struct GameConfig {
  int maxAttempts = 10;
};

struct GameState {
  std::string word;
  std::vector<bool> revealed;
  std::vector<char> guessedLetters;
  int attemptsRemaining = 0;
};

bool isAlphaLetter(char ch) {
  unsigned char uch = static_cast<unsigned char>(ch);
  return (uch >= 'A' && uch <= 'Z') || (uch >= 'a' && uch <= 'z');
}

char normalizeLetter(char ch) {
  return static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
}

std::string formatMaskedWord(const std::string& word, const std::vector<bool>& revealed) {
  std::string out;
  out.reserve(word.size() * 2);
  for (size_t i = 0; i < word.size(); ++i) {
    out.push_back(revealed[i] ? word[i] : '_');
    if (i + 1 < word.size()) out.push_back(' ');
  }
  return out;
}

std::string formatGuessedLetters(const std::vector<char>& guessedLetters) {
  std::string out;
  out.reserve(guessedLetters.size() * 2);
  for (size_t i = 0; i < guessedLetters.size(); ++i) {
    out.push_back(guessedLetters[i]);
    if (i + 1 < guessedLetters.size()) out.push_back(' ');
  }
  return out;
}

std::vector<std::string> defaultWords() { return {"CAT", "DOG", "FISH", "BIRD", "COW", "MOUSE", "RAT"}; }

std::string pickRandomWord(const std::vector<std::string>& words, unsigned int seed) {
  if (words.empty()) return {};
  std::mt19937 rng(seed);
  std::uniform_int_distribution<size_t> dist(0, words.size() - 1);
  std::string word = words[dist(rng)];
  for (char& ch : word) ch = normalizeLetter(ch);
  return word;
}

bool hasRevealedAll(const std::vector<bool>& revealed) {
  return std::all_of(revealed.begin(), revealed.end(), [](bool v) { return v; });
}

void drawHangmanStage(int wrongGuesses) {
  wrongGuesses = std::clamp(wrongGuesses, 0, 6);

  std::cout << "  +---+\n";
  std::cout << "  |   |\n";

  std::cout << (wrongGuesses >= 1 ? "  O   |\n" : "      |\n");

  if (wrongGuesses >= 4) {
    std::cout << " /|\\  |\n";
  } else if (wrongGuesses == 3) {
    std::cout << " /|   |\n";
  } else if (wrongGuesses == 2) {
    std::cout << "  |   |\n";
  } else {
    std::cout << "      |\n";
  }

  if (wrongGuesses >= 6) {
    std::cout << " / \\  |\n";
  } else if (wrongGuesses == 5) {
    std::cout << " /    |\n";
  } else {
    std::cout << "      |\n";
  }

  std::cout << "      |\n";
  std::cout << "=========\n";
}

unsigned int parseSeed(int argc, char** argv) {
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
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

bool tryReadGuessLetter(char& outLetter) {
  std::string input;
  if (!std::getline(std::cin >> std::ws, input)) return false;
  if (input.empty()) return false;

  char ch = input[0];
  if (!isAlphaLetter(ch)) return false;
  outLetter = normalizeLetter(ch);
  return true;
}

void printTurn(const GameState& state, const GameConfig& config) {
  int wrongGuesses = config.maxAttempts - state.attemptsRemaining;

  std::cout << "\nAttempts remaining: " << state.attemptsRemaining << "\n";
  drawHangmanStage(wrongGuesses);
  std::cout << "Word:   " << formatMaskedWord(state.word, state.revealed) << "\n";
  std::cout << "Guessed:"
            << (state.guessedLetters.empty() ? " (none)" : " " + formatGuessedLetters(state.guessedLetters))
            << "\n";
}

bool applyGuess(GameState& state, const GameConfig& config, char guess) {
  if (std::find(state.guessedLetters.begin(), state.guessedLetters.end(), guess) != state.guessedLetters.end()) {
    std::cout << "You've already guessed '" << guess << "'. Try a different letter.\n";
    return false;
  }

  state.guessedLetters.push_back(guess);

  bool correct = false;
  for (size_t i = 0; i < state.word.size(); ++i) {
    if (state.word[i] == guess) {
      state.revealed[i] = true;
      correct = true;
    }
  }

  if (!correct) {
    state.attemptsRemaining = std::max(0, state.attemptsRemaining - 1);
    std::cout << "Incorrect guess.\n";
  } else {
    std::cout << "Correct!\n";
  }

  return true;
}

int runGame(int argc, char** argv) {
  GameConfig config;
  const unsigned int seed = parseSeed(argc, argv);

  const std::vector<std::string> words = defaultWords();
  if (words.empty()) {
    std::cerr << "Error: word list is empty.\n";
    return 1;
  }

  GameState state;
  state.word = pickRandomWord(words, seed);
  if (state.word.empty()) {
    std::cerr << "Error: failed to select a word.\n";
    return 1;
  }
  state.revealed.assign(state.word.size(), false);
  state.attemptsRemaining = config.maxAttempts;

  std::cout << "Welcome to Hangman!\n";
  std::cout << "The word has " << state.word.size() << " letters.\n";
  std::cout << "Tip: run with --seed <number> for reproducible games.\n";

  while (state.attemptsRemaining > 0 && !hasRevealedAll(state.revealed)) {
    printTurn(state, config);

    std::cout << "Enter a letter: ";
    char guess = '\0';
    if (!tryReadGuessLetter(guess)) {
      std::cout << "Invalid input. Please enter a single letter (A-Z).\n";
      continue;
    }

    applyGuess(state, config, guess);
  }

  printTurn(state, config);
  if (hasRevealedAll(state.revealed)) {
    std::cout << "\nCongratulations! You've guessed the word: " << state.word << "\n";
  } else {
    std::cout << "\nGame over! The word was: " << state.word << "\n";
  }

  return 0;
}

}  // namespace

int main(int argc, char** argv) { return runGame(argc, argv); }
