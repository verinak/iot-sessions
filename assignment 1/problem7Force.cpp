
#include <iostream>
#include <cmath>
using namespace std;

const double UNIVERSAL_GRAVITATIONAL = 6.6743*pow(10,-8);    //define a constant constant global variable
double calc_force(double m1,double m2,double distance);      //declare the calc_force function 

int main()
{   
    double m1;
    double m2;
    double distance;
    char calcAgain;

    do {
        // get user input for m1, m2, d
        cout << "Enter m1: " << endl;
        cin>>m1;

        cout << "Enter m2: " << endl;
        cin>>m2;

        cout << "Enter d: " << endl;
        cin>>distance;

        // invoke the function and store the return value in variable of same type
        double force = calc_force(m1, m2, distance);
        cout<<"\nGravitational Force = "<<force << endl;

        // check if user would like to calculate again
        // if user doesn't input 'y' the loop stops
        cout << "\nWould you like to calculate again? (y/n) ";
        cin >> calcAgain;
    }
    while(calcAgain == 'y'); // if the user enters "n" the program will stop
    
    return 0;
}

double calc_force(double m1,double m2,double distance){       
    //function definition outside the main
    double force = UNIVERSAL_GRAVITATIONAL*m1*m2/pow(distance,2);
    return force;
}
