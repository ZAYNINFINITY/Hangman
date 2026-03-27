#pragma once

#include <string>

namespace hangman {

enum class Category {
  Animals,
  Countries,
  Movies,
};

const char* categoryId(Category category);
std::string categoryDisplayName(Category category);
bool tryParseCategoryId(const std::string& id, Category& out);

}  // namespace hangman

