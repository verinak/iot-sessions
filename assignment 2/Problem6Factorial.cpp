#include <iostream>

using namespace std;

int main() {
  int n;
  int factorial = 1;

  // Ask the user to enter a positive integer
  cout << "Enter a positive integer: ";
  cin >> n;

  // Check if the input is a positive integer
  while (n <= 0) {
    // If not,ask the user to enter a positive integer again
    cout << "Please enter a positive integer: ";
    cin >> n;
  }

  // Calculate the factorial of n using a loop
  for (int i = 1; i <= n; ++i) {
    factorial *= i;
  }

  // Print the factorial to the console
  cout << "The factorial of " << n << " is " << factorial << endl;

  return 0;
}
