#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int calc_max_product (vector<int> arr, int n);

int main()
{
    int n, max_product;
    // ask the user to enter array size
    cout << "Enter the size of the array:\n ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter the elements of the array:\n ";
    // store the numbers that the user entered in the array
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "The array you entered is:\n ";
    // print the array elements to the user
    for (int j = 0; j < n; j++) {
        cout << arr[j] << " ";
    }
    cout << endl;

    sort(arr.begin(), arr.end());
    max_product = calc_max_product(arr, n);

    return 0;
}

// function to calculate the maximum three integers from the array
int calc_max_product(vector<int> arr, int n) {

    int max_p = arr[n - 1] * arr[n - 2] * arr[n - 3];

     // print the maximum product
    cout << "The maximum product of any three integers from the array is: " << max_p << endl;

    // print the three integers
    cout << "The three integers are: " << arr[n - 1] << " , " << arr[n - 2] << " , " << arr[n - 3] << endl;
    return max_p;
}
