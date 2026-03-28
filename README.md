# 🎮 Hangman Game (C++)

![Hangman Banner](https://img.shields.io/badge/Hangman-C++-blue?style=for-the-badge&logo=cplusplus)  
[![Version](https://img.shields.io/badge/version-1.0-brightgreen.svg)]()  
[![License](https://img.shields.io/badge/license-MIT-green.svg)]()  
[![Platform](https://img.shields.io/badge/platform-Console-lightgrey.svg)]()  

---

## 📌 About

A simple **console-based Hangman game** written in **C++**.  
The player guesses letters to reveal a hidden word before the hangman drawing is completed.  

---

## ✨ Features

- 🎯 Randomly selected words  
- 🔠 Tracks correct & wrong guesses  
- 🖥️ Console interface with ASCII hangman stages  
- ❌ Limited number of incorrect tries  
- 🗂️ Word categories (Animals, Countries, Movies)
- 🪟 Windows GUI (category selector)

---

## ⚙️ Requirements

- C++11 or higher  
- g++ / clang++ / MSVC compiler  
- Works on Windows, Linux, macOS (console only)  

---

## 🚀 Build & Run
### Build CLI (legacy single-file)
On Windows (MSVC) or with g++/clang++ installed:
- `g++ -std=c++11 -O2 -o hangman hangman.cpp`
- `./hangman`

### Build GUI (Windows, MSVC)
From a “Developer Command Prompt for VS” (so `cl` is available):
- `cl /EHsc /std:c++17 src\\core\\HangmanGame.cpp src\\core\\WordBank.cpp src\\core\\Category.cpp src\\core\\WordRepository.cpp src\\gui\\win32_main.cpp /link user32.lib gdi32.lib comctl32.lib /SUBSYSTEM:WINDOWS /OUT:hangman_gui.exe`
- `./hangman_gui.exe`

### Build with CMake (recommended)
If you have CMake installed:
- `cmake -S . -B build`
- `cmake --build build --config Release`

Outputs:
- `hangman_cli` (core-based CLI with categories)
- `hangman_cli_legacy` (single-file CLI)
- `hangman_gui` (Windows GUI)
- `hangman_tests` (unit tests)

### Run (category mode)
- `./hangman_cli --category animals --seed 123`
- `./hangman_cli --category countries`

### Word lists
Word lists live in `data/words/*.txt` (one word per line). Non-alphabetic entries and out-of-range word lengths are skipped.

### Roadmap
- See `docs/LEVELS_BLUEPRINT.md` for the 30-level campaign blueprint and task breakdown.

🔮 Future Improvements
Difficulty levels (Easy / Hard)

External word list file support

Better ASCII art (colored output)

Multiplayer mode (player vs player)

---

🤝 Contributing
Pull requests and ideas are welcome!
If you’d like to improve the game, fork the repo and submit a PR.



📜 License
This project is licensed under the MIT License.
See the LICENSE file for details.
