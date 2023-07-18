#include <stdio.h>
#include<iostream>
#include <cctype>

using namespace std ;


// Function to sort an array using bubble sort Algorithm 
/*side notes : the algorithm will perform (n-1) passes /iterations ,
 and in each iteration the number of comp decreases by i (n-i-1)*/
 
int* bubblesort(int arr[], int n) {
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(arr[j+1] < arr[j]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
    return arr;
}

int main() {
    //declare and intialize the array i want to sort 
    int myArray[] = {5, 2, 8, 1, 3};

    //sizeof() returns the size of a variable or a data type in bytes.
    int n = sizeof(myArray) / sizeof(myArray[0]);
    
    // bubblesort function return a pointer to first element
    int* sortedArray = bubblesort(myArray, n);

    //for loop to just Print the sorted array
    for(int i = 0; i < n; i++) {
        cout << sortedArray[i] << " ";
    }
    cout << endl;

    return 0;
}