#include <iostream>

using namespace std;

double calc_avrg (int arr[] , int n );

int main()
{
    int n ;
    double average;
    // ask the user to enter array size
    cout << " Enter the size of the array:\n " ;
    cin >> n;

    int arr [n];
    cout << " Enter the " << n << " integers of the array:\n " ;
    // store the numbers that the user entered in the array
    for( int i = 0 ; i < n ; i++) {

         cin >> arr[i];
    }

    cout << " The array's numbers are :\n " ;
    // print the array elements to the user
    for( int j = 0 ; j < n ; j++) {

         cout << arr[j] << " " ;
    }
     cout<<"\n";

    average = calc_avrg ( arr , n );

    return 0;
}
// function to calculate the average
double calc_avrg (int arr[] , int n ){
    int sum = 0;
    for (int i =0 ; i < n ; i++){
        sum += arr[i];
    }

    double avrg;
    avrg = static_cast <double> (sum) / n;
    cout << "The average of all the numbers is: " << avrg ;

    return avrg;
}
