
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

void displayWord(const string& word, const vector<bool>& guessed) {
    for (int i = 0; i < word.length(); ++i) {
        if (guessed[i]) {
            cout << word[i] << " ";
        } else {
            cout << "_ ";
        }
    }
    cout << endl;
}

void drawHangman(int attempts) {
    cout << "  +---+" << endl;
    cout << "  |   |" << endl;
    
    if (attempts <= 6) cout << "  O   |" << endl; 
    else cout << "      |" << endl;

    if (attempts <= 4) cout << " /|\\  |" << endl; 
    else if (attempts == 5) cout << " /|   |" << endl; 
    else cout << "      |" << endl;

    if (attempts <= 2) cout << " / \\  |" << endl; 
    else if (attempts == 3) cout << " /    |" << endl; 
    else cout << "      |" << endl;

    cout << "      |" << endl;
    cout << "=========" << endl;
}

int main() {
    vector<string> words = {"CAT", "DOG", "FISH", "BIRD", "COW", "MOUSE", "RAT"};
    srand(static_cast<unsigned int>(time(0)));
    string word = words[rand() % words.size()]; 
    vector<bool> guessed(word.length(), false); 
    vector<char> guessedLetters; // To keep track of guessed letters
    int attempts = 10; 
    char guess; 
    bool wordGuessed = false;

    cout << "Welcome to Hangman!" << endl;
    cout << "The word has " << word.length() << " letters." << endl; 

    while (attempts > 0 && !wordGuessed) {
        cout << "\nAttempts remaining: " << attempts << endl;
        drawHangman(attempts); 
        displayWord(word, guessed);

        cout << "Enter a letter: ";
        cin >> guess;
        guess = toupper(guess); 

        if (find(guessedLetters.begin(), guessedLetters.end(), guess) != guessedLetters.end()) {
            cout << "You've already guessed that letter. Try again!" << endl;
            continue; 
        }

        guessedLetters.push_back(guess); // Add the guessed letter to the list

        bool correctGuess = false;
        for (int i = 0; i < word.length(); ++i) {
            if (word[i] == guess) {
                guessed[i] = true; 
                correctGuess = true;
            }
        }

        if (!correctGuess) {
            attempts--;
            cout << "Incorrect guess!" << endl;
        }

        wordGuessed = true;
        for (bool g : guessed) {
            if (!g) {
                wordGuessed = false; 
                break;
            }
        }
    }

    if (wordGuessed) {
        cout << "\nCongratulations! You've guessed the word: " << word << endl;
    } else {
        cout << "\nGame over! The word was: " << word << endl;
        drawHangman(0); 
    }

    return 0;
}