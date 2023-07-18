#include <iostream>

using namespace std;

// function to print the first line with two spaces and a given character three times
void printLine1(char inputCharacter) {
    for(int i = 0; i < 2; i++){
            cout << " ";
    }
    for(int i = 0; i < 3; i++){
        cout << inputCharacter;
    }
    cout << "\n";
}

// function to print the second line with a given character, two spaces, and the given character again
void printLine2(char inputCharacter) {
    for(int i = 0; i < 2; i++){
        cout << " " << inputCharacter << " ";
    }
    cout << "\n";
}

int main() {
    
    // define char variable and take it as user input
    char inputCharacter;
    cout << "\nEnter a character: ";
    cin >> inputCharacter;
    cout << "\n";

    // print the first two lines using defined functions
    printLine1(inputCharacter);
    printLine2(inputCharacter);
    // print 5 lines with the given input character
    for(int i = 0; i < 5; i++){
        cout << inputCharacter << "\n";
    }
    // print the first two lines in reverse
    printLine2(inputCharacter);
    printLine1(inputCharacter);

    return 0;
}
