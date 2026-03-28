# Progress Tracker

This file tracks what’s implemented versus what’s planned in `docs/LEVELS_BLUEPRINT.md`.

## Status

- Level 1: In progress (CLI refactor + core tests done)
- Level 2: In progress (categories + file loader + CLI/GUI wiring)
- Level 3: In progress (CI + build hygiene)
- Level 4: In progress (difficulty presets)
- Level 5+: Not started

## Level 1 Notes

Completed:
- Refactored `hangman.cpp` into `runGame()` and helper functions.
- Added robust letter input handling (alpha validation + multi-character handling).
- Fixed hangman drawing to scale with `maxAttempts`.
- Added `--seed` and `--seed=<n>` for reproducible CLI games.
- Added initial core unit tests via CMake (`tests/hangman_tests.cpp`).

## Level 2 Notes

Completed:
- Added word lists in `data/words/` for Animals/Countries/Movies.
- Added `Category` model and parsing helpers.
- Added `FileWordRepository` with trimming and validation.
- Wired category selection into GUI and the new core-based CLI.
- Added tests for file word loading and validation.
- Updated README to document categories and word list format.

## Level 3 Notes

Completed:
- Added `.gitignore` for build/IDE outputs.
- Added GitHub Actions CI workflow for CMake build + tests.
- Enabled warnings in CMake and defined `HANGMAN_VERSION`.
- Added `--help` and `--version` to the core-based CLI.
- Added public headers under `include/`.

## Level 4 Notes

Completed:
- Added `Difficulty` model and parsing helpers.
- Added `Ruleset` tables mapping difficulty to attempts/multiplier.
- Wired difficulty selection into CLI and GUI.
- Added unit tests for difficulty and ruleset behavior.
