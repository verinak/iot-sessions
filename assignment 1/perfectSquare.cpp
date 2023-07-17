#include <iostream>
#include <math.h>

using namespace std;

bool isPerfectSquare(int n)
{
    // sqrt() method is defined in the math.h library
    // to return the square root of a given number
    int x = sqrt(n);
    //a perfect square is when an integer is multiplied by itself
    //like 4 is a perfect square of 2 (2*2)
    if (x * x == n)
        return true;
    else
        return false;
}

void  reverseDigits(int n)
{
    int reversed_num=0;
 cout << "you entered: "<<n<<"\n";
    while(n!=0){
        //for the first loop reversed_num is 0*10=0 +modulus gives us the last digit of a number
        //ex:12345 for first loop reversed_num=0+5=5
        //division by 10 to get rid of the last digit (int/int=int)
       reversed_num=reversed_num*10;
       reversed_num=reversed_num+n%10;
       //cout<<reversed_num<<"\n";
       n =n/10;//updating statements
       //cout<<n<<"\n";
    }
    cout << "\nReversed number is: "<<reversed_num;
    cout << "\n\n";
}

void calculateSum(int n)
{
    //sum each digit from the end of the number using modulus
    //and divide by 10 to get rid of the number we summed for not summing it again
   int sum=0;
   while(n!=0){
        sum += n % 10;
        n = n/10;
    }
    cout <<"\nSum of digits: " << sum;
    cout << "\n\n";

}

int main()
{
    cout << "Hello, this program can: " << "\n";
    cout << "1.determine if an integer is a perfect square"<< "\n" <<"2.reverse this integer "<< "\n" << "3.calculate the sum of its digits :)" << "\n";


    int n;
    //a boolean variable
    bool perfect = false;
    cout << "Enter a positive integer : "<<"\n";
    cin >> n;
    // Calling a method that returns true if the
    // number is a perfect square and storing it in a boolean variable
    perfect = isPerfectSquare(n);
     //if condition to decide if the number is a perfect square or not
    if (perfect)
    {
        cout << "\nThe entered number " << n << " is a perfect square of the number " << sqrt(n);
    }
    else
    {
        cout << "\nThe entered number " << n << " is not a perfect square";
    }

cout << "\n\n";

//calling the 2 void functions to print the reverse and the sum of the number
   reverseDigits(n);
   calculateSum(n);


    return 0;
}



