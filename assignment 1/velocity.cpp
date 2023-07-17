#include <iostream>

using namespace std;

int main()
{
    double velocity; // initialize the variable velocity
    double tc_start;  // initialize the starting degree of temperature variable
    double tc_end;   //  initialize the ending degree of temperature variable

    cout << "Enter the starting temperature:" << endl; //print statement
    cin>>tc_start;     //store the input of the user in tc_start variable

    cout << "Enter the ending temperature:" << endl;  //print statement
    cin>>tc_end;      //store the input of the user in tc_end variable

    while(tc_start<=tc_end){      //while loop stops when the starting temperature becomes greater than the ending temperature
        velocity = 331.3 + 0.61 * tc_start;   //calculate the velocity
        cout<<"At "<<tc_start<<" degrees Celsius the velocity of sound is "<< velocity<<"m/s"<<endl;  //print the velocity at specific tempreture
        tc_start++;      //increment the starting temperature by 1 for the next itaration
    }
    return 0;
}
