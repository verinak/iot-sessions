#include <stdio.h>
#include<iostream>
#include <cctype>

using namespace std ;

const double liter_per_gallon= 1.0/0.264179;

double miles_per_gallon_func(double liters , double miles ){
    double miles_per_gallon,gallons ;
    gallons = liters / liter_per_gallon;
    miles_per_gallon= miles / gallons ;
    return miles_per_gallon ;
}
int main()
{
    //define constatnt for the number of liters per gallon
    double liters ;
    double miles , miles_per_gallon;
    char flag ;
    char agree ='y' ;
    do{
    cout << "Enter number of liters consumed : ";
    cin >> liters;
    cout << "Enter number of miles : " ;
    cin >> miles;
    miles_per_gallon = miles_per_gallon_func(liters, miles);
    cout<< "the number of miles per gallon the car delivered : " << miles_per_gallon << endl ; 

    cout<< "do you want to recalculate ?"<< "\n" <<"(y/n)" << endl ;
    cin >> flag;
    
    }while(toupper(flag)== toupper(agree));
    return 0 ;
}
