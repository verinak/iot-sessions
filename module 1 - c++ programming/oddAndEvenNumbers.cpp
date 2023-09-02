#include <iostream>

using namespace std;

int main() {
    
    int num1,num2;
    cout << "\nEnter 2 numbers: ";
    cin >> num1 >> num2;

    if((num1%2 == 0) & (num2%2 == 0)) {
        cout <<"Sum: " << num1 + num2 << "\n";
    }
    else if((num1%2 != 0) & (num2%2 != 0)) {
        cout <<"Product: " << num1 * num2 << "\n";
    }
    else if((num1%2 != 0) & (num2%2 == 0)) {
        cout <<"Difference: " << num2 - num1 << "\n";
    }
    else {
        cout <<"Difference: " << num1 - num2 << "\n";
    }

    return 0;
}
