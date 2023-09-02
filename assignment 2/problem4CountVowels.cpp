#include <iostream>

using namespace std;

int count_vowels(const char* str) {    // Function to count the number of vowels in a string
  int count = 0;

  for (const char* p = str; *p != '\0'; ++p) {   //Loop through each character in the string using a pointer
    if (*p == 'a' || *p == 'e' || *p == 'i' || *p == 'o' || *p == 'u' ||
        *p == 'A' || *p == 'E' || *p == 'I' || *p == 'O' || *p == 'U') {
      count++;
    }
  }

  return count;
}

int main() {
  char str[100];  // Declare a character array to store the user input

  cout << "Enter a string: ";
  cin.getline(str, 100);

  int vowels = count_vowels(str);
  // Call the count_vowels() function with the input string as its argument
  cout << "Number of vowels: " << vowels << endl;

  return 0;
}
