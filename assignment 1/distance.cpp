#include <iostream>

using namespace std;

double distance_fun ( double time , int accel , double pro, double dis);

int main()
{
    // Declare variables
     double time, product, distance, result;
     int acceleration= 32;

    // asked the user to enter the time in seconds
    cout << "Enter the time in seconds: " <<"\n" ;
    cin >> time;

     result= distance_fun(time , acceleration, product ,distance);
    return 0;
}

// function to calculate the distance that the object would drop in
double distance_fun ( double time , int acce , double pro, double dis)
 {
     pro = acce * time * time ;
     cout << "The product is: " << pro <<"\n";
     dis = pro/2 ;
      //  print the distance to the user
     cout << "The distance that the object would drop in: " << dis <<"\n" ;

    return dis;
}
