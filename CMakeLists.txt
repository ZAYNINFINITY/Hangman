cmake_minimum_required(VERSION 3.20)
project(Hangman LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(hangman_core
  src/core/HangmanGame.cpp
  src/core/WordBank.cpp
  src/core/Category.cpp
  src/core/WordRepository.cpp
)
target_include_directories(hangman_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

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
