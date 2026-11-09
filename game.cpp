#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>
#include <ctime>
using namespace std;

int main();
void ShowTitleScreen();
void clearScreen();
void pauseScreen();
void MainInterface();
void ShowFlowerList();
void ShowStats();
void ShowFlowerTells();
void PlayBloomMath();
void PlayPollenWords();
void PlayGrowAStory();
void PlayRPSGame();

const int COLOR_BG = 15;   // White background
const int COLOR_TITLE = 11; // Light cyan
const int COLOR_TEXT = 7;  // Light gray
const int COLOR_GOOD = 10; // Light green
const int COLOR_BAD = 12;  // Light red
const int COLOR_INFO = 14; // Yellow

// ─── Main Function ─────────────────────────────────
int main() {
    srand(time(0)); // Seed the random number generator with the current time
    
    ShowTitleScreen(); // Show the title screen
    int choice;
    
    do{
        MainInterface(); // Call the main interface function to start the program
        cin >> choice;
    
        switch (choice) {
            case 1: PlayBloomMath(); break;
            case 2: PlayPollenWords(); break;
            case 3: PlayGrowAStory(); break;
            case 4: PlayRPSGame(); break;
            case 5: ShowFlowerTells(); break;
            case 0: return 0;
            default:
                cout << "Invalid choice!\n";
                pauseScreen();
                MainInterface();
                break;
        }
    }while (choice != 0);

    return 0;
}

void setColor(int fg, int bg = 0) { //fg means foreground(text) color, bg means background color
    /*HANDLE is a Windows data type.
    It represents a connection to something managed by Windows. In this case, it represents the console screen
    GetStdHandle
    This Windows function gets a handle to the standard output.
    STD_OUTPUT_HANDLE means:
    Get the console where text is printed.
    The result is stored in: h ,, You can think of h as an address or reference to the console screen.*/ 
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, fg | (bg << 4));
    /*This Windows function changes the console’s text and background colors.
    It needs two things:
    1. The console handle: h
    2. The color setting
    fg | (bg << 4)
    This combines the foreground color and background color into one value.
    bg << 4
    The << here is a bit-shift operator.
    It moves the background color four binary positions to the left.

    Windows stores colors like this:
    Background color | Text color
    
    so kapag setColor(12, 0);
        cout << "This is light red text.\n";
    The text becomes light red with a black background.*/
    
}

void clearScreen() {
    system("cls");
}

void pauseScreen() {
    setColor(COLOR_INFO);
    cout << "\nPress ENTER to continue...";
    cin.ignore();
    cin.get();
}
void ShowTitleScreen() {
    clearScreen();
    setColor(COLOR_TITLE);
    cout << "NIWA MIND\n";
    setColor(COLOR_TEXT);
    cout << "Welcome to the NIWA MIND game!\n";
    pauseScreen();
}
void MainInterface() {
    clearScreen();
    setColor(COLOR_TITLE);
    cout << "NIWA MIND\n";
    setColor(COLOR_TEXT);
    cout << "1. Bloom Math\n";
    cout << "2. Pollen Words\n";
    cout << "3. Grow A Story\n";
    cout << "4. Janken Pon\n";
    cout << "5. Show Flower Tells \n";
    cout << "0. Exit\n";
    cout << "\nChoose an option: ";
    
}

void ShowStats() {
    cout << "Stats coming soon.";
    pauseScreen();
}

void ShowFlowerTells() {
    cout << "Flower Tells coming soon.";
    pauseScreen();
}

void PlayBloomMath() {
    clearScreen();
    int choice;
    cout << "1. Easy\n";
    cout << "2. Medium\n";
    cout << "3. Hard\n";
    cout << "0. Back\n";
    cout << "Choose a difficulty: ";
    cin >> choice;
    switch(choice){
        case 1:
            cout << "Easy Bloom Math coming soon.";
            pauseScreen();
            break;
        case 2:
            cout << "Medium Bloom Math coming soon.";
            pauseScreen();
            break;
        case 3:
            cout << "Hard Bloom Math coming soon.";
            pauseScreen();
            break;
        case 0:
            return;
        default:
            cout << "Invalid choice!\n";
            pauseScreen();
            break;
    }
}

void PlayPollenWords() {
    cout << "Pollen Words coming soon.";
    pauseScreen();
}
void PlayGrowAStory() {
    cout << "Grow A Story coming soon.";
    pauseScreen();
}
void PlayRPSGame() {
    cout << "Rock-Paper-Scissors coming soon.";
    pauseScreen();
}
void ShowFlowerList() {
    cout << "Flower List coming soon.";
    pauseScreen();
}