#include "core/Category.hpp"

#include <algorithm>

namespace hangman {

const char* categoryId(Category category) {
  switch (category) {
    case Category::Animals:
      return "animals";
    case Category::Countries:
      return "countries";
    case Category::Movies:
      return "movies";
  }
  return "unknown";
}

std::string categoryDisplayName(Category category) {
  switch (category) {
    case Category::Animals:
      return "Animals";
    case Category::Countries:
      return "Countries";
    case Category::Movies:
      return "Movies";
  }
  return "Unknown";
}

bool tryParseCategoryId(const std::string& id, Category& out) {
  std::string lowered = id;
  std::transform(lowered.begin(), lowered.end(), lowered.begin(),
                 [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

  if (lowered == "animals") {
    out = Category::Animals;
    return true;
  }
  if (lowered == "countries") {
    out = Category::Countries;
    return true;
  }
  if (lowered == "movies") {
    out = Category::Movies;
    return true;
  }
  return false;
}

}  // namespace hangman

