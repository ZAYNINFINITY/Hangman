#include "core/WordRepository.hpp"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace hangman {
namespace {

std::string trim(std::string s) {
  auto notSpace = [](unsigned char c) { return !std::isspace(c); };

  s.erase(s.begin(), std::find_if(s.begin(), s.end(), notSpace));
  s.erase(std::find_if(s.rbegin(), s.rend(), notSpace).base(), s.end());
  return s;
}

bool isAlphaOnly(const std::string& s) {
  if (s.empty()) return false;
  for (unsigned char c : s) {
    if (!(c >= 'A' && c <= 'Z') && !(c >= 'a' && c <= 'z')) return false;
  }
  return true;
}

std::string toUpper(std::string s) {
  std::transform(s.begin(), s.end(), s.begin(),
                 [](unsigned char c) { return static_cast<char>(std::toupper(c)); });
  return s;
}

}  // namespace

FileWordRepository::FileWordRepository(std::filesystem::path baseDir) : baseDir_(std::move(baseDir)) {
  if (baseDir_.empty()) {
    throw std::invalid_argument("baseDir must not be empty");
  }
}

WordLoadResult FileWordRepository::load(Category category, const WordValidationOptions& options) {
  WordLoadResult result;

  std::filesystem::path file = baseDir_ / (std::string(categoryId(category)) + ".txt");
  std::ifstream in(file);
  if (!in.is_open()) {
    result.warnings.push_back("Failed to open word list: " + file.string());
    return result;
  }

  std::string line;
  size_t lineNo = 0;
  while (std::getline(in, line)) {
    ++lineNo;
    std::string word = trim(line);
    if (word.empty()) continue;

    if (word.size() < options.minLength || word.size() > options.maxLength) {
      std::ostringstream msg;
      msg << "Skipping invalid word length at " << file.string() << ":" << lineNo;
      result.warnings.push_back(msg.str());
      continue;
    }

    if (!isAlphaOnly(word)) {
      std::ostringstream msg;
      msg << "Skipping non-alpha word at " << file.string() << ":" << lineNo;
      result.warnings.push_back(msg.str());
      continue;
    }

    result.words.push_back(toUpper(word));
  }

  if (result.words.empty()) {
    result.warnings.push_back("No valid words loaded from: " + file.string());
  }

  return result;
}

}  // namespace hangman

