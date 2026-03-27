#include <windows.h>

#include <chrono>
#include <string>

#include "core/HangmanGame.hpp"
#include "core/WordBank.hpp"

namespace {

constexpr int kIdGuessEdit = 101;
constexpr int kIdGuessButton = 102;
constexpr int kIdNewGameButton = 103;

constexpr int kIdMaskedStatic = 201;
constexpr int kIdAttemptsStatic = 202;
constexpr int kIdGuessedStatic = 203;
constexpr int kIdStatusStatic = 204;

std::wstring toWide(const std::string& s) {
  if (s.empty()) return L"";
  int needed = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, nullptr, 0);
  if (needed <= 0) return L"";
  std::wstring out(static_cast<size_t>(needed), L'\0');
  MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, out.data(), needed);
  if (!out.empty() && out.back() == L'\0') out.pop_back();
  return out;
}

void setText(HWND hwnd, int controlId, const std::wstring& text) {
  SetWindowTextW(GetDlgItem(hwnd, controlId), text.c_str());
}

std::wstring getText(HWND hwnd, int controlId) {
  HWND h = GetDlgItem(hwnd, controlId);
  int len = GetWindowTextLengthW(h);
  std::wstring buf(static_cast<size_t>(len + 1), L'\0');
  int written = GetWindowTextW(h, buf.data(), len + 1);
  buf.resize(static_cast<size_t>(std::max(0, written)));
  return buf;
}

struct UiState {
  hangman::HangmanGame game{hangman::HangmanConfig{10}};
  std::vector<std::string> words = hangman::WordBank::defaultWords();
};

unsigned int timeSeed() {
  auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
  return static_cast<unsigned int>(
      std::chrono::duration_cast<std::chrono::microseconds>(now).count());
}

void refreshUi(HWND hwnd, UiState& state) {
  setText(hwnd, kIdMaskedStatic, L"Word: " + toWide(state.game.maskedWord()));
  setText(hwnd, kIdAttemptsStatic,
          L"Attempts: " + std::to_wstring(state.game.attemptsRemaining()));
  setText(hwnd, kIdGuessedStatic,
          L"Guessed: " + toWide(state.game.guessedLettersString()));

  if (state.game.isWon()) {
    setText(hwnd, kIdStatusStatic, L"You won! Click New Game to play again.");
  } else if (state.game.isLost()) {
    setText(hwnd, kIdStatusStatic, L"You lost! Word was: " + toWide(state.game.word()));
  } else {
    setText(hwnd, kIdStatusStatic, L"Enter a letter, then click Guess.");
  }
}

void startNewGame(HWND hwnd, UiState& state) {
  std::string w = hangman::WordBank::randomWord(state.words, timeSeed());
  state.game.startNewRound(std::move(w));
  setText(hwnd, kIdGuessEdit, L"");
  refreshUi(hwnd, state);
}

void showStatus(HWND hwnd, const wchar_t* msg) {
  setText(hwnd, kIdStatusStatic, msg);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
  static UiState* ui = nullptr;
  switch (msg) {
    case WM_CREATE: {
      ui = new UiState();

      CreateWindowW(L"STATIC", L"Hangman (GUI)",
                    WS_CHILD | WS_VISIBLE, 20, 15, 340, 20, hwnd, nullptr,
                    nullptr, nullptr);

      CreateWindowW(L"STATIC", L"", WS_CHILD | WS_VISIBLE,
                    20, 45, 420, 20, hwnd, (HMENU)kIdMaskedStatic, nullptr, nullptr);
      CreateWindowW(L"STATIC", L"", WS_CHILD | WS_VISIBLE,
                    20, 70, 420, 20, hwnd, (HMENU)kIdAttemptsStatic, nullptr, nullptr);
      CreateWindowW(L"STATIC", L"", WS_CHILD | WS_VISIBLE,
                    20, 95, 420, 20, hwnd, (HMENU)kIdGuessedStatic, nullptr, nullptr);
      CreateWindowW(L"STATIC", L"", WS_CHILD | WS_VISIBLE,
                    20, 120, 520, 20, hwnd, (HMENU)kIdStatusStatic, nullptr, nullptr);

      CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
                    20, 155, 80, 24, hwnd, (HMENU)kIdGuessEdit, nullptr, nullptr);
      CreateWindowW(L"BUTTON", L"Guess", WS_CHILD | WS_VISIBLE,
                    110, 155, 80, 24, hwnd, (HMENU)kIdGuessButton, nullptr, nullptr);
      CreateWindowW(L"BUTTON", L"New Game", WS_CHILD | WS_VISIBLE,
                    200, 155, 100, 24, hwnd, (HMENU)kIdNewGameButton, nullptr, nullptr);

      startNewGame(hwnd, *ui);
      return 0;
    }

    case WM_COMMAND: {
      const int id = LOWORD(wparam);
      if (!ui) return 0;

      if (id == kIdNewGameButton) {
        startNewGame(hwnd, *ui);
        return 0;
      }

      if (id == kIdGuessButton) {
        if (ui->game.isWon() || ui->game.isLost()) {
          showStatus(hwnd, L"Round finished. Click New Game.");
          return 0;
        }

        std::wstring text = getText(hwnd, kIdGuessEdit);
        if (text.empty()) {
          showStatus(hwnd, L"Enter a letter first.");
          return 0;
        }
        wchar_t wch = text[0];
        wch = static_cast<wchar_t>(towupper(wch));
        if (wch < L'A' || wch > L'Z') {
          setText(hwnd, kIdGuessEdit, L"");
          showStatus(hwnd, L"Invalid input. Use A-Z.");
          refreshUi(hwnd, *ui);
          return 0;
        }
        char ch = static_cast<char>(wch);

        auto result = ui->game.guessLetter(ch);
        setText(hwnd, kIdGuessEdit, L"");

        switch (result) {
          case hangman::GuessResult::Correct:
            showStatus(hwnd, L"Correct!");
            break;
          case hangman::GuessResult::Incorrect:
            showStatus(hwnd, L"Incorrect.");
            break;
          case hangman::GuessResult::Duplicate:
            showStatus(hwnd, L"Already guessed.");
            break;
          case hangman::GuessResult::Invalid:
            showStatus(hwnd, L"Invalid input. Use A-Z.");
            break;
        }
        refreshUi(hwnd, *ui);
        return 0;
      }
      return 0;
    }

    case WM_DESTROY:
      if (ui) {
        delete ui;
        ui = nullptr;
      }
      PostQuitMessage(0);
      return 0;
  }
  return DefWindowProcW(hwnd, msg, wparam, lparam);
}

}  // namespace

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow) {
  const wchar_t kClassName[] = L"HangmanGuiWindow";

  WNDCLASSW wc{};
  wc.lpfnWndProc = WndProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = kClassName;
  wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

  RegisterClassW(&wc);

  HWND hwnd = CreateWindowExW(
      0, kClassName, L"Hangman (GUI)", (WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME),
      CW_USEDEFAULT, CW_USEDEFAULT, 620, 260, nullptr, nullptr, hInstance, nullptr);

  if (!hwnd) return 0;

  ShowWindow(hwnd, nCmdShow);

  MSG msg{};
  while (GetMessageW(&msg, nullptr, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessageW(&msg);
  }
  return 0;
}
