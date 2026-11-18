#include <iostream>
#include <windows.h>
#include <cmath>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <limits>
using namespace std;

struct Gamedata {
    int points = 0;
    int bloomMathPoints = 0;
    int pollenWordsPoints = 0;
    int jankenPonPoints = 0;
};
Gamedata gameData;

void clearScreen();
void pauseScreen();

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
            input == 'S') {
            return input;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice. Please enter 1, 2, 3, 0, or S: ";
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

int ReadPlayAgain(){
    int choice;
    while(!cin.fail()){
        cin >> choice;
        if(choice == 1 || choice == 2 || choice == 3 || choice == 0){
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice. Please enter 1, 2, 3, or 0: ";
    }
    return 0;
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
    return 0;
}

// ─── Main Function ─────────────────────────────────
int main() {
    srand(time(0));
    cout << fixed << setprecision(2);

    int choice;
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
        }
    } while (choice != 0 && choice != '0');

    cout << "\nFinal total points: " << gameData.points << "\n";
    cout << "Thank you for playing Niwa Mind! Goodbye!\n";
    return 0;
}

void clearScreen() {
    system("cls"); //This command clears the console screen on Windows systems. It is a system call that executes the "cls" command in the command prompt, effectively clearing all text from the console window.
}

void pauseScreen() { 
    cout << "\nPress ENTER to continue..."; // Prompt the user to press ENTER to continue
    cin.get(); // Wait for the user to press ENTER before proceeding
}

void menuChoice() {
    clearScreen();
    cout << "\n==================== NIWA MIND ====================\n"
         << "Welcome to Niwa Mind, a collection of fun and educational games!\n"
         << "Help your flower bloom by playing distinct games that challenge your mind and creativity.\n";
    cout << "\nTotal points: " << gameData.points << "\n";

    cout << "1. Bloom Math\n"
         << "2. Pollen Words\n"
         << "3. Janken Pon\n\n"
         << "[S] Stats Counter    [0] Exit\n"
         << "\nChoose an option: ";
}

int bloomMathEasy() {
    int lives = 3;
    int numQuestions = 15, numCorrectAnswers = 0;
    double userAnswer;
    int correctAnswer;
    clearScreen();
    cout << "You chose Easy difficulty. Solve simple addition and subtraction problems.\n";

    
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
            gameData.points += 1;
            gameData.bloomMathPoints += 1;
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
    cout << "You chose Medium difficulty. Solve multiplication and division problems.\n";

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
            gameData.points += 2;
            gameData.bloomMathPoints += 2;
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
    cout << "You chose Hard difficulty. Solve complex math problems.\n";

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
            gameData.points += 3;
            gameData.bloomMathPoints += 3;
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
        choiceBM = ReadPlayAgain();
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
             << "1 point for each Easy problem solved.\n"
             << "2 points for each Medium problem solved.\n"
             << "3 points for each Hard problem solved.\n"
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
    int numQuestions = 10, numCorrectAnswers = 0;
    int counter = 1;
    string userAnswer, answer;
    string clue1, clue2, clue3;

    while (lives > 0 && counter <= numQuestions) {
        int questionPoints = 3;

        switch (counter) {
            case 1:
                clue1 = "A fruit that keeps the doctor away.";
                clue2 = "A fruit that is often red or green.";
                clue3 = "A fruit that is often associated with teachers.";
                answer = "apple";
                break;
            case 2:
                clue1 = "A large mammal with a trunk.";
                clue2 = "A mammal that is often found in Africa and Asia.";
                clue3 = "A mammal that is known for its intelligence and memory.";
                answer = "elephant";
                break;
            case 3:
                clue1 = "A celestial body that orbits a planet.";
                clue2 = "A celestial body that is often visible at night.";
                clue3 = "A celestial body that affects tides on Earth.";
                answer = "moon";
                break;
            case 4:
                clue1 = "A device used to take photographs.";
                clue2 = "A device that captures images using light.";
                clue3 = "A device that can be digital or film-based.";
                answer = "camera";
                break;
            case 5:
                clue1 = "A type of tree known for its acorns.";
                clue2 = "A tree that is often found in forests and parks.";
                clue3 = "A tree that is often associated with autumn.";
                answer = "oak";
                break;
            case 6:
                clue1 = "A type of bird known for its colorful feathers.";
                clue2 = "A bird that is often found in tropical regions.";
                clue3 = "A bird that is known for its ability to mimic sounds.";
                answer = "parrot";
                break;
            case 7:
                clue1 = "A type of flower that is often associated with love.";
                clue2 = "A flower that is often red in color.";
                clue3 = "A flower that is commonly given as a gift.";
                answer = "rose";
                break;
            case 8:
                clue1 = "A type of vehicle that runs on tracks.";
                clue2 = "A vehicle that is often used for public transportation.";
                clue3 = "A vehicle that can be powered by electricity or diesel.";
                answer = "train";
                break;
            case 9:
                clue1 = "A type of fruit that is often yellow in color.";
                clue2 = "A fruit that is often found on trees.";
                clue3 = "A fruit that is known for its sweet taste.";
                answer = "banana";
                break;
            case 10:
                clue1 = "A type of insect that produces honey.";
                clue2 = "An insect that lives in colonies.";
                clue3 = "An insect that is known for its ability to make wax.";
                answer = "bee";
                break;
        }

        cout << "\nWord " << counter << "/" << numQuestions
             << "\nLives: " << lives
             << "\nClue 1: " << clue1;

        if (revealCluePW() == 1) {
            cout << "Clue 2: " << clue2;
            questionPoints = 2;

            if (revealCluePW() == 1) {
                cout << "Clue 3: " << clue3 << "\n";
                questionPoints = 1;
            }
        }

        cout << "\nYour answer (Q to quit): ";
        cin >> userAnswer;

        if (userAnswer == answer) {
            cout << "Correct! You earned " << questionPoints << " points.\n";
            gameData.points += questionPoints;
            gameData.pollenWordsPoints += questionPoints;
            numCorrectAnswers++;
        } else if (userAnswer == "q" || userAnswer == "Q") {
            return -1; // User chose to quit
        } else {
            cout << "Incorrect. The answer is " << answer << ".\n";
            lives--;
        }

        counter++;
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

        cin >> choicePW;
        if (choicePW < 0 || choicePW > 2) {
            cout << "Invalid choice. Please try again.\n\n";
        }
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
         << "A correct answer earns 3 points after Clue 1, 2 after Clue 2, or 1 after Clue 3.\n"
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

        cin >> choiceJP;
        if (choiceJP < 0 || choiceJP > 2) {
            cout << "Invalid choice. Please try again.\n\n";
        }
    } while (choiceJP < 0 || choiceJP > 2);

    return choiceJP;
}

int jankenPon() {
    int lives = 3;
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

    while (choiceJP == 1 && lives > 0) {
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
            gameData.points += 1;
            gameData.jankenPonPoints += 1;
        } else if (userChoice == "q" || userChoice == "Q") {
            return 2;
        } else {
            cout << "You lose!\n";
            lives--;
        }
        // NOTE: Added a 5-second pause before clearing the screen to allow the player to see the result of the round.
        this_thread::sleep_for(chrono::seconds(5));
        clearScreen();
    }

    return 0;
}

void statsCounter() {
    clearScreen();
    int totalPoints = gameData.bloomMathPoints + gameData.pollenWordsPoints
                    + gameData.jankenPonPoints;

    cout << "\n==================== STATS COUNTER ====================\n"
         << "Bloom Math: " << gameData.bloomMathPoints << " points\n"
         << "Pollen Words: " << gameData.pollenWordsPoints << " points\n"
         << "Janken Pon: " << gameData.jankenPonPoints << " points\n"
         << "-------------------------------------------------------\n"
         << "Total points: " << totalPoints << "\n";
    pauseScreen();
}