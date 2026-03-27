# Progress Tracker

This file tracks what’s implemented versus what’s planned in `docs/LEVELS_BLUEPRINT.md`.

## Status

- Level 1: In progress (CLI refactor + core tests done)
- Level 2+: Not started

## Level 1 Notes

Completed:
- Refactored `hangman.cpp` into `runGame()` and helper functions.
- Added robust letter input handling (alpha validation + multi-character handling).
- Fixed hangman drawing to scale with `maxAttempts`.
- Added `--seed` and `--seed=<n>` for reproducible CLI games.
- Added initial core unit tests via CMake (`tests/hangman_tests.cpp`).

