
#include <iostream>
#include <cmath>
using namespace std;
const double universal_gravitational= 6.6743*pow(10,-8);
double calc_force(double m1,double m2,double distance);
int main()
{   double m1;
    double m2;
    double distance;
    cout << "Enter g1" << endl;
    cin>>m1;

    cout << "Enter g2" << endl;
    cin>>m2;

    cout << "Enter d" << endl;
    cin>>distance;

    double force = calc_force(m1, m2, distance);
    cout<<force;
    return 0;
}
double calc_force(double m1,double m2,double distance){
        double force =universal_gravitational*m1*m1/pow(distance,2);
        return force;


    }
