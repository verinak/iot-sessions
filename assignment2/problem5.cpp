#include <iostream>

using namespace std;

int num()
{
    int arr_size; // Initializing a variables
    int sum = 0;
    cout << "Enter the size of the array: " << endl;
    cin >> arr_size; // Taking from the user the size of the array
    int nums[arr_size]; // Creating an integer array, its size the user will enter it.
    cout << "Enter integer numbers (up to " << arr_size << " numbers):" << endl;

    // for-loop that iterate over the array to calculate the sum of the numbers in the array
    for(int i = 0; i < arr_size; i++){

            cin >> nums[i];
            sum += nums[i];}
          cout << "The sum = " << sum << endl; // Display the sum of the numbers.

}
