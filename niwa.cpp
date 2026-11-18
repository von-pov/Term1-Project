#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <thread>
#include <chrono>
#include <limits>
#include "word_bank.h"
using namespace std;

struct Gamedata {
    string selectedFlower;
    int points = 0;
    int bloomMathPoints = 0;
    int pollenWordsPoints = 0;
    int jankenPonPoints = 0;
    int notesUnlocked = 0;
};
Gamedata gameData;

void clearScreen();
void pauseScreen();

void showtitle();
void menuChoice();
void statsCounter();
int bloomMathEasy();
int bloomMathMedium();
int bloomMathHard();
int gameOverBM(int lives);
int bloomMath();

int revealCluePW();
int QnAPW();
int gameOverPW(int lives);
int pollenWords();
void showFlowerList();
void updateFlowerTells();
void showFlowerTells();
void showFlowerStory(const string& flower, int notesUnlocked);


int gameOverJP(int lives);
int jankenPon();



// ---- Input validation functions ----

char getMainMenuInput() {
    char input;
    while (true) {
        cin >> input;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        input = toupper(input);

        if ((input >= '0' && input <= '3') ||
            input == 'S' || input == 'N' || input == 'F') {
            return input;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice. Please enter 1, 2, 3, 0, N, F, or S: ";
    }
}

char getYesNoInput(){
    char input;
    while(true){
        cin >> input;
        input = toupper(input);
        if(input == 'Y' || input == 'y' || input == 'N' || input == 'n'){
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return input;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter Y or N: ";
    }
}

bool readMathAnswer(double& answer) {
    string input;

    while (true) {
        cin >> input;

        if (input == "q" || input == "Q") {
            return false;
        }

        try {
            size_t position; // Variable to hold the position of the first invalid character in the input string.
            answer = stod(input, &position); // Convert the input string to a double using stod. The position variable will be updated to indicate where the conversion stopped.

            if (position == input.length()) { // Check if the entire input string was successfully converted to a double.
                return true;
            }
        } catch (...) { // Catch any exceptions thrown by stod (e.g., invalid input).
            // The input was not a valid number.
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid answer. Enter a number or Q to quit: ";
    }
}

int getIntegerInput(int minimum, int maximum){
    int value;
    while(true){
        cin >> value;
        if(!cin.fail() && value >= minimum && value <= maximum){
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "Invalid input. Enter a number from " << minimum
             << " to " << maximum << ": ";
    }
}

int ReadStartGame() {
    char choice;

    while (true) {
        cin >> choice;
        choice = toupper(choice);

        if (choice == 'S' || choice == 's') {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return 1;
        }

        if (choice == 'B' || choice == 'b') {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return 0;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice. Please enter S or B: ";
    }
}

int ReadDifficultyLevel(){
    int choice;
    while(true){
        cin >> choice;
        if(!cin.fail() && (choice == 1 || choice == 2 || choice == 3 || choice == 0)){
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice. Please enter 1, 2, 3, or 0: ";
    }
}

// ─── Main Function ─────────────────────────────────
int main() {
    srand(time(0));
    cout << fixed << setprecision(2);
    showtitle();

    int choice;
     if (gameData.selectedFlower.empty()) { // If no flower is selected, show the flower list
        showFlowerList();
    } else {
        cout << "Your flower is: " << gameData.selectedFlower << '\n';
        cout << "Your points are: " << gameData.points << '\n';
    }

    do {
        menuChoice();
        choice = getMainMenuInput();
        switch (choice) {
            case '1':
                if (bloomMath() == 0) {
                    choice = 0;
                }
                break;
            case '2':
                if (pollenWords() == 0) {
                    choice = 0;
                }
                break;
            case '3':
                if (jankenPon() == 0) {
                    choice = 0;
                }
                break;
            case 'S':
                statsCounter();
                break;
            case 'N':
                showFlowerTells();
                break;
            case 'F':
                showFlowerList();
                break;
        }
    } while (choice != 0 && choice != '0');

    cout << "\nFinal total points: " << gameData.points << "\n";
    cout << "Thank you for playing Niwa! Goodbye!\n";
    return 0;
}

void clearScreen() {
    system("cls"); //This command clears the console screen on Windows systems. It is a system call that executes the "cls" command in the command prompt, effectively clearing all text from the console window.
}

void pauseScreen() { 
    cout << "\nPress ENTER to continue..."; // Prompt the user to press ENTER to continue
    cin.get(); // Wait for the user to press ENTER before proceeding
}

void showtitle(){
    clearScreen();
    cout << "\n\n\n           N" << flush;
    this_thread::sleep_for(chrono::seconds(1));

    cout << "I" << flush;
    this_thread::sleep_for(chrono::seconds(1));

    cout << "W" << flush;
    this_thread::sleep_for(chrono::seconds(1));

    cout << "A\n" << flush;
    this_thread::sleep_for(chrono::seconds(1));

    cout << "\n\n      Blooming" << flush;
    this_thread::sleep_for(chrono::seconds(1));

    cout << " Minds\n\n" << flush;
    this_thread::sleep_for(chrono::seconds(1));

    pauseScreen();
}

void menuChoice() {
    clearScreen();
    cout << "\n================== NIWA: Blooming Minds ==================\n"
         << "Welcome to Niwa Mind, a collection of fun and educational games!\n"
         << "Help your flower bloom by playing distinct games that challenge your mind and creativity.\n";
    cout << "\nTotal points: " << gameData.points << "\n";

    cout << "1. Bloom Math\n"
         << "2. Pollen Words\n"
         << "3. Janken Pon\n\n"
         << "[N] Flower tells     [S] Stats Counter\n"
         << "[F] Flower           [0] Exit\n"
         << "\nChoose an option: ";
}
void updateFlowerTells() {
    if (gameData.points >= 50) {
        gameData.notesUnlocked = 1;
    }
    if (gameData.points >= 100) {
        gameData.notesUnlocked = 2;
    }
    if (gameData.points >= 150) {
        gameData.notesUnlocked = 3;
    }
}
void showFlowerTells() {
    clearScreen();
    updateFlowerTells();

    cout << "--- FLOWER TELLS ---\n\n";

    if (gameData.selectedFlower.empty()) {
        cout << "Choose a flower first.\n";
        pauseScreen();
        return;
    }

    cout << "Flower: " << gameData.selectedFlower << "\n"
         << "Notes unlocked: " << gameData.notesUnlocked
         << "\n\n";

    showFlowerStory(
        gameData.selectedFlower,
        gameData.notesUnlocked
    );

    pauseScreen();
}

void showFlowerStory(const string& flower, int notesUnlocked){
    ifstream file("flowertells.txt");

    if (!file) {
        cout << "The flowertells.txt file could not be found.\n";
        return;
    }

    if (notesUnlocked == 0) {
        cout << "No Flower Tells have been unlocked yet.\n";
        return;
    }

    string line;
    string flowerHeader = "[" + flower + "]";
    bool foundFlower = false;
    int noteNumber = 0;

    while (getline(file, line)) {
        if (line == flowerHeader) {
            foundFlower = true;
            continue;
        }

        if (foundFlower && !line.empty() && line.front() == '[') {
            break;
        }

        if (foundFlower && !line.empty() && noteNumber < notesUnlocked) {
            noteNumber++;
            cout << "Note " << noteNumber << ": " << line << "\n\n";
        }
    }

    if (!foundFlower) {
        cout << "No story was found for the selected flower.\n";
    }
}



int bloomMathEasy() {
    int lives = 3;
    int numQuestions = 15, numCorrectAnswers = 0;
    double userAnswer;
    int correctAnswer;
    clearScreen();
    cout << "You chose Easy difficulty.\nSolve simple addition and subtraction problems.\n";

    
    while (lives > 0 && numCorrectAnswers < numQuestions) {
        int num1 = rand() % 100 + 1;
        int num2 = rand() % 100 + 1;
        int operation = rand() % 2;

        cout << "\nLives: " << lives;

        if (operation == 0) {
            correctAnswer = num1 + num2;
            cout << "\nWhat is " << num1 << " + " << num2 << "? (Q to quit): ";
        } else {
            correctAnswer = num1 - num2;
            cout << "\nWhat is " << num1 << " - " << num2 << "? (Q to quit): ";
        }

        if (!readMathAnswer(userAnswer)) {
            return -1;
        }

        if (userAnswer == correctAnswer) {
            cout << "Correct!\n";
            gameData.points += 2;
            gameData.bloomMathPoints += 2;
            updateFlowerTells();
            numCorrectAnswers++;
        } else {
            cout << "Incorrect. The answer is " << correctAnswer << ".\n";
            lives--;
        }
        this_thread::sleep_for(chrono::seconds(3));
        clearScreen();
    }

    cout << "\nCorrect answers: " << numCorrectAnswers << "/" << numQuestions
         << "\nTotal points: " << gameData.points << "\n";
    return lives;
}

int bloomMathMedium() {
    int lives = 3;
    int numQuestions = 15, numCorrectAnswers = 0;
    double userAnswer, correctAnswer;
    clearScreen();
    cout << "You chose Medium difficulty.\nSolve multiplication and division problems.\n";

    while (lives > 0 && numCorrectAnswers < numQuestions) {
        int num1 = rand() % 100 + 1;
        int num2 = rand() % 100 + 1;
        int operation = rand() % 2;

        cout << "\nLives: " << lives;

        if (operation == 0) {
            correctAnswer = num1 * num2;
            cout << "\nWhat is " << num1 << " * " << num2 << "? (Q to quit): ";
        } else {
            correctAnswer = round((1.0 * num1 / num2) * 100.0) / 100.0;
            cout << "\nWhat is " << num1 << " / " << num2
                 << " (Round to 2 decimal places; Q to quit)? ";
        }

        if (!readMathAnswer(userAnswer)) {
            return -1;
        }

        if (userAnswer == correctAnswer) {
            cout << "Correct!\n";
            gameData.points += 5;
            gameData.bloomMathPoints += 5;
            updateFlowerTells();
            numCorrectAnswers++;
        } else {
            cout << "Incorrect. The answer is " << correctAnswer << ".\n";
            lives--;
        }
        this_thread::sleep_for(chrono::seconds(3));
        clearScreen();
    }

    cout << "\nCorrect answers: " << numCorrectAnswers << "/" << numQuestions
         << "\nTotal points: " << gameData.points << "\n";
    return lives;
}

int bloomMathHard() {
    int lives = 3;
    int numQuestions = 15, numCorrectAnswers = 0;
    double userAnswer, correctAnswer;
    clearScreen();
    cout << "You chose Hard difficulty.\nSolve complex math problems.\n";

    while (lives > 0 && numCorrectAnswers < numQuestions) {
        int num1 = rand() % 100 + 1;
        int num2 = rand() % 100 + 1;
        int operation = rand() % 4;

        cout << "\nLives: " << lives;

        if (operation == 0) {
            correctAnswer = (num1 + num2) * (num2 - num1);
            cout << "\nWhat is (" << num1 << " + " << num2
                 << ") * (" << num2 << " - " << num1 << ")? (Q to quit) ";
        } else if (operation == 1) {
            correctAnswer = (num1 * num2) - (num2 * num1);
            cout << "\nWhat is (" << num1 << " * " << num2
                 << ") - (" << num2 << " * " << num1 << ")? (Q to quit) ";
        } else if (operation == 2) {
            correctAnswer = round((1.0 * num1 * num2 / (num2 * num1)) * 100.0) / 100.0;
            cout << "\nWhat is (" << num1 << " * " << num2
                 << ") / (" << num2 << " * " << num1
                 << ") (Round to 2 decimal places; Q to quit)? ";
        } else {
            correctAnswer = round((1.0 * num1 * num2 / (num2 + num1)) * 100.0) / 100.0;
            cout << "\nWhat is (" << num1 << " * " << num2
                 << ") / (" << num2 << " + " << num1
                 << ") (Round to 2 decimal places; Q to quit)? ";
        }

        if (!readMathAnswer(userAnswer)) {
            return -1;
        }

        if (userAnswer == correctAnswer) {
            cout << "Correct!\n";
            gameData.points += 10;
            gameData.bloomMathPoints += 10;
            updateFlowerTells();
            numCorrectAnswers++;
        } else {
            cout << "Incorrect. The answer is " << correctAnswer << ".\n";
            lives--;
        }
        this_thread::sleep_for(chrono::seconds(3));
        clearScreen();
    }

    cout << "\nCorrect answers: " << numCorrectAnswers << "/" << numQuestions
         << "\nTotal points: " << gameData.points << "\n";
    return lives;
}

int gameOverBM(int lives) {
    int choiceBM;

    if (lives == 0) {
        cout << "\nGame over!\n";
    } else {
        cout << "\nDifficulty cleared! Your flower blooms!\n";
    }

    do {
        cout << "1. Play this difficulty again\n"
             << "2. Choose another difficulty level\n"
             << "3. Other games\n"
             << "0. Exit\n"
             << "\nChoose an option: ";
        // CHANGED: Add input validation for choiceBM
        choiceBM = getIntegerInput(0, 3);
        if (choiceBM < 0 || choiceBM > 3) {
            cout << "Invalid choice. Please try again.\n\n";
        }
    } while (choiceBM < 0 || choiceBM > 3);

    return choiceBM;
}

int bloomMath() {
    int option;
    int level = 1;
    int lives = 3;
    int choiceBM = 2; // Show the difficulty menu first.

    do {
        clearScreen();
        cout << "\n==================== BLOOM MATH ====================\n"
             << "Welcome to Bloom Math! Solve a problem to help your flower bloom.\n"
             << "2 points for each Easy problem solved.\n"
             << "3 points for each Medium problem solved.\n"
             << "5 points for each Hard problem solved.\n"
             << "Get 15 correct answers before losing all 3 lives.\n";
    
        cout << "\n[S] Start the game         [B] Back to main menu\n"
             << "\n"
             << "\nChoose an option: ";
        // CHANGED: Add input validation for option
        option = ReadStartGame();
    } while (option != 0 && option != 1);

    if (option == 0) {
        return 3;
    }

    while (choiceBM != 3 && choiceBM != 0) {
        if (choiceBM == 2) {
            do {
                clearScreen();
                cout << "1. Easy\n"
                     << "2. Medium\n"
                     << "3. Hard\n"
                     << "0. Back to main menu\n"
                     << "\nChoose a difficulty level: ";
                // CHANGED: Add input validation for level
                level = ReadDifficultyLevel();
                if (level < 0 || level > 3) {
                    cout << "Invalid choice. Please try again.\n\n";
                }
            } while (level < 0 || level > 3);
        }

        switch (level) {
            case 1:
                lives = bloomMathEasy();
                break;
            case 2:
                lives = bloomMathMedium();
                break;
            case 3:
                lives = bloomMathHard();
                break;
            case 0:
                return 3; // Return to main menu
                break;
        }

        choiceBM = gameOverBM(lives);
    }

    return choiceBM; // 0 = exit; 3 = return to the main menu.
}

int revealCluePW() {
    string decision;
    int choice = -1;

    do {
        cout << "\nReveal next clue? (y/n): ";
        cin >> decision;

        if (decision == "y") {
            choice = 1;
        } else if (decision == "n") {
            choice = 0;
        } else {
            cout << "Invalid input. Please enter 'y' or 'n'.\n";
        }
    } while (choice < 0);

    return choice;
}

int QnAPW() {
    int lives = 3;
    int numQuestions = wordBankSize, numCorrectAnswers = 0;
    int counter = 1;
    string userAnswer, answer;
    string clue1, clue2, clue3;
    clearScreen();
    while (lives > 0 && counter <= numQuestions) {
        int questionPoints = 5;

        const WordEntry& currentWord = wordBank[counter - 1];
        answer = currentWord.word;
        clue1 = currentWord.clue1;
        clue2 = currentWord.clue2;
        clue3 = currentWord.clue3;
        
        cout << "\nWord: " << counter
             << "\nNumber of questions: " << numQuestions
             << "\nLives: " << lives
             << "\n\nClue 1: " << clue1;

        if (revealCluePW() == 1) {
            cout << "\nClue 2: " << clue2;
            questionPoints = 3;

            if (revealCluePW() == 1) {
                cout << "\nClue 3: " << clue3 << "\n";
                questionPoints = 2;
            }
        }

        cout << "\nYour answer (Q to quit): ";
        cin >> userAnswer;

        if (userAnswer == answer) {
            cout << "Correct! You earned " << questionPoints << " points.\n";
            gameData.points += questionPoints;
            gameData.pollenWordsPoints += questionPoints;
            updateFlowerTells();
            numCorrectAnswers++;
        } else if (userAnswer == "q" || userAnswer == "Q") {
            return -1; // User chose to quit
        } else {
            cout << "Incorrect. The answer is " << answer << ".\n";
            lives--;
        }

        counter++;
        this_thread::sleep_for(chrono::seconds(3));
        clearScreen();
    }

    cout << "\nCorrect answers: " << numCorrectAnswers << "/" << numQuestions
         << "\nTotal points: " << gameData.points << "\n";
    return lives;
}

int gameOverPW(int lives) {
    int choicePW;

    if (lives == 0) {
        cout << "\nGame over!\n";
    } else {
        cout << "\nCongratulations! You have completed the puzzle!\n";
    }

    do {
        cout << "1. Play Pollen Words again\n"
             << "2. Other games\n"
             << "0. Exit\n"
             << "\nChoose an option: ";

        choicePW = getIntegerInput(0, 2);
    } while (choicePW < 0 || choicePW > 2);

    return choicePW;
}

int pollenWords() {
    int option;
    int lives;
    int choicePW = 1;
    clearScreen();
    cout << "\n==================== POLLEN WORDS ====================\n"
         << "Guess each word using up to 3 clues. Enter answers in lowercase.\n"
         << "A correct answer earns 5 points after Clue 1, 3 after Clue 2, or 2 after Clue 3.\n"
         << "Wrong answers cost 1 life. Revealing clues does not remove your saved points.\n"
         << "Complete 10 word puzzles before losing all 3 lives.\n";

    do {
        cout << "\n[S] Start the game         [B] Back to main menu\n"
             << "\n"
             << "\nChoose an option: ";
        option = ReadStartGame();
        
    } while (option < 0 || option > 1);

    if (option == 0) {
        return 2;
    }

    while (choicePW == 1) {
        lives = QnAPW();
        choicePW = gameOverPW(lives);
    }

    return choicePW;
}

int gameOverJP(int lives) {
    int choiceJP;
    clearScreen();

    if (lives == 0) {
        cout << "\nGame over!\n";
    } else {
        cout << "\nCongratulations! You have completed the game!\n";
    }

    do {
        cout << "1. Play Janken Pon again\n"
             << "2. Other games\n"
             << "0. Exit\n"
             << "\nChoose an option: ";

        choiceJP = getIntegerInput(0, 2);
    } while (choiceJP < 0 || choiceJP > 2);

    return choiceJP;
}

int jankenPon() {
    int lives;
    int option;
    string userChoice, computerChoice;
    int choiceJP = 1;
    do {
        clearScreen();
        cout << "\n==================== JANKEN PON ====================\n"
             << "Play Rock-Paper-Scissors against the computer.\n"
             << "Win to earn 1 point. Draws do not affect points or lives.\n"
             << "You have 3 lives. Good luck!\n";

    
        cout << "\n[S] Start the game         [B] Back to main menu\n"
             << "\n"
             << "\nChoose an option: ";
        option = ReadStartGame();
    } while (option < 0 || option > 1);

    if (option == 0) {
        return 2;
    }

    while (choiceJP == 1) {
        lives = 3;

        while (lives > 0) {
        int validChoice = 0;
        cout << "\nLives: " << lives;

            while (validChoice == 0) {
                cout << "\nChoose Rock (r), Paper (p), or Scissors (s)  [Q to quit]: ";
                cin >> userChoice;

                if (userChoice == "r" || userChoice == "p" || userChoice == "s") {
                    validChoice = 1;
                } else if (userChoice == "q" || userChoice == "Q") {
                    return 2;
                } else {
                    cout << "Invalid choice. Please enter only r, p, s, or q.\n";
                }
            }

        cout << "\nJan..." << flush;
        this_thread::sleep_for(chrono::seconds(1));

        cout << " Ken..." << flush;
        this_thread::sleep_for(chrono::seconds(1));

        cout << " Pon!\n" << flush;
        this_thread::sleep_for(chrono::seconds(1));

        int computerRandom = rand() % 3;
        if (computerRandom == 0) {
            computerChoice = "r";
        } else if (computerRandom == 1) {
            computerChoice = "p";
        } else {
            computerChoice = "s";
        }

        cout << "Computer chose: " << computerChoice << "\n";

        if (userChoice == computerChoice) {
            cout << "It's a draw!\n";
        } else if ((userChoice == "r" && computerChoice == "s") ||
                   (userChoice == "p" && computerChoice == "r") ||
                   (userChoice == "s" && computerChoice == "p")) {
            cout << "You win!\n";
            gameData.points += 2;
            gameData.jankenPonPoints += 2;
            updateFlowerTells();
        } else if (userChoice == "q" || userChoice == "Q") {
            return 2;
        } else {
            cout << "You lose!\n";
            lives--;
        }
        // NOTE: Added a 3-second pause before clearing the screen to allow the player to see the result of the round.
        this_thread::sleep_for(chrono::seconds(3));
        clearScreen();
        }

        choiceJP = gameOverJP(lives);
    }

    return choiceJP;
}



void showFlowerList() {
    int choice;
    char confirm;
    string chosenFlower;

    clearScreen();
    cout << "--- FLOWER GARDEN ---\n\n";
    cout << "1. Sunflower\n"
         << "   Meaning: Hope and happiness\n"
         << "   Theme: Finding light during difficult times\n\n"
         << "2. Rose\n"
         << "   Meaning: Love and courage\n"
         << "   Theme: Caring for others despite challenges\n\n"
         << "3. Lotus\n"
         << "   Meaning: Growth and overcoming struggles\n"
         << "   Theme: Rising above a difficult beginning\n\n"
         << "4. Cherry Blossom\n"
         << "   Meaning: Change and memories\n"
         << "   Theme: Accepting the temporary nature of life\n\n"
         << "5. Lavender\n"
         << "   Meaning: Peace and healing\n"
         << "   Theme: Recovering from sadness\n\n"
         << "6. Orchid\n"
         << "   Meaning: Uniqueness and patience\n"
         << "   Theme: Becoming confident in your differences\n\n"
         << "0. Back\n\n"
         << "Choose a flower: ";

    choice = getIntegerInput(0, 6);

    switch (choice) {
        case 1: chosenFlower = "Sunflower"; break;
        case 2: chosenFlower = "Rose"; break;
        case 3: chosenFlower = "Lotus"; break;
        case 4: chosenFlower = "Cherry Blossom"; break;
        case 5: chosenFlower = "Lavender"; break;
        case 6: chosenFlower = "Orchid"; break;
        case 0: return;
        default:
            cout << "Invalid choice!\n";
            pauseScreen();
            return;
    }

    cout << "\nYou selected: " << chosenFlower
         << "\nDo you want to grow this flower? (Y/N): ";
    confirm = getYesNoInput();

    if (confirm == 'Y') {
        gameData.selectedFlower = chosenFlower;
        cout << "\nYour " << gameData.selectedFlower << " has been selected!\n";
    } else {
        cout << "\nYour flower selection was cancelled.\n";
    }

    pauseScreen();
}

void statsCounter() {
    clearScreen();
    int totalPoints = gameData.bloomMathPoints + gameData.pollenWordsPoints
                    + gameData.jankenPonPoints;

    cout << "\n==================== STATS COUNTER ====================\n"
         << "Chosen Flower: " << gameData.selectedFlower << "\n"
         << "Bloom Math: " << gameData.bloomMathPoints << " points\n"
         << "Pollen Words: " << gameData.pollenWordsPoints << " points\n"
         << "Janken Pon: " << gameData.jankenPonPoints << " points\n"
         << "-------------------------------------------------------\n"
         << "Total points: " << totalPoints << "\n";
    pauseScreen();
}