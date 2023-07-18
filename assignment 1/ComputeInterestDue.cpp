#include <iostream>

using namespace std;


   #include <iostream>

using namespace std;

// Function to calculate the interest, total amount and minimum payment
void Calculations(double bal, double& InterestDue, double& TotalAmount, double& MinPayment) {
    cout << "Enter your Balance: ";
        cin >> bal;

    if (bal > 1000) { //Calculating the interest using if condition, if balance > 1000 or not
        InterestDue = (1000 * 0.015) + ((bal - 1000) * 0.01);
    } else {
        InterestDue = bal * 0.015;
    }
    TotalAmount = InterestDue + bal; //Calculating the total amount

    if (TotalAmount <= 10) {  //Calculating minimum payment using if condition too
        MinPayment = TotalAmount;
    } else {
        MinPayment = max(10.0, TotalAmount * 0.1);
    }
}

int main()
{
    char x;
    double bal, InterestDue, TotalAmount, MinPayment;

    //do-while loop to repeat the calculations based on user's opinion
    do {
        Calculations(bal, InterestDue, TotalAmount, MinPayment);

        cout << "Interest Due = " << InterestDue << endl;
        cout << "Total Amount = " << TotalAmount << endl;
        cout << "Minimum Payment = " << MinPayment << endl;
        cout << "Do you want to repeat the calculations ? (Y/N)" << endl;
        cin >> x;

    } while(x == 'Y' || x == 'y');

    cout << "The Program stopped." << endl;
}


