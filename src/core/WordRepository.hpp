#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include "core/Category.hpp"

namespace hangman {

struct WordValidationOptions {
  size_t minLength = 2;
  size_t maxLength = 32;
};

struct WordLoadResult {
  std::vector<std::string> words;
  std::vector<std::string> warnings;
};

class FileWordRepository {
 public:
  explicit FileWordRepository(std::filesystem::path baseDir);

  WordLoadResult load(Category category, const WordValidationOptions& options = {});

 private:
  std::filesystem::path baseDir_;
};

}  // namespace hangman

