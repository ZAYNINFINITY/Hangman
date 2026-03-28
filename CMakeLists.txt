cmake_minimum_required(VERSION 3.20)
project(Hangman VERSION 1.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(hangman_core
  src/core/HangmanGame.cpp
  src/core/WordBank.cpp
  src/core/Category.cpp
  src/core/Difficulty.cpp
  src/core/WordRepository.cpp
  src/core/Ruleset.cpp
)
target_include_directories(hangman_core PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(MSVC)
  target_compile_options(hangman_core PRIVATE /W4 /permissive-)
else()
  target_compile_options(hangman_core PRIVATE -Wall -Wextra -Wpedantic)
endif()

target_compile_definitions(hangman_core PUBLIC HANGMAN_VERSION="${PROJECT_VERSION}")

# Legacy CLI (kept as-is)
add_executable(hangman_cli
  src/cli/main.cpp
)
target_link_libraries(hangman_cli PRIVATE hangman_core)

add_executable(hangman_cli_legacy hangman.cpp)

# GUI (Windows-only for now)
if(WIN32)
  add_executable(hangman_gui WIN32
    src/gui/win32_main.cpp
  )
  target_link_libraries(hangman_gui PRIVATE hangman_core user32 gdi32 comctl32)
  target_compile_definitions(hangman_gui PRIVATE UNICODE _UNICODE)
endif()

enable_testing()
add_executable(hangman_tests
  tests/hangman_tests.cpp
)
target_link_libraries(hangman_tests PRIVATE hangman_core)
add_test(NAME hangman_tests COMMAND hangman_tests)
