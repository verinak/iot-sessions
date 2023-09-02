#include <iostream>

using namespace std;

int main()
{
    // Declaring array that its size = 5, consists of 5 numbers
    int numbers [] = {5,10,15,20,25};
    int sum = 0;
    // for-loop that iterate over the array to calculate the sum of the numbers in the array
    for(int i = 0; i < 5; i++){
        sum += numbers[i];
    }
    // Displaying the sum of the numbers in the array
    cout << "The Sum of the numbers = " << sum;

}

