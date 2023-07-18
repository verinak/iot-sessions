#include <iostream>

using namespace std;

double cost_per_square_inch( double diameter, double price);

int main()
{
  // Declare variables
  double diameter_S , diameter_L, price_S , price_L ;
  double cost_for_Small_pizza , cost_for_large_pizza ;

  // asked the user to enter the data for  the two pizzas
 cout << "Enter a small pizza's diameter: " << "\n";
    cin>>diameter_S;

    cout << "Enter a small pizza's price: " << "\n";
    cin>>price_S;

    cout<< "Enter a large pizza's diameter: "<< "\n";
    cin>>diameter_L;

    cout<< "Enter a large pizza's price: "<< "\n";
    cin>>price_L;

  // compute the price per square inch for small pizza
  cost_for_Small_pizza =  cost_per_square_inch(diameter_S, price_S);

  cout<< "the price per square inch for small pizza: "<< cost_for_Small_pizza << "\n";

  // compute the price per square inch for large pizza
  cost_for_large_pizza =  cost_per_square_inch(diameter_L, price_L);

  cout<< "the price per square inch for large pizza: "<<cost_for_large_pizza <<"\n";

  //determine which is the better buy pizza
  if ( cost_for_Small_pizza < cost_for_large_pizza){
    cout << "The small pizza is the better buy\n ";
  }
  else if ( cost_for_large_pizza < cost_for_Small_pizza){
         cout << "The large pizza is the better buy\n";
    }
  else{
     cout << "The small pizza is the better buy\n";
  }
    return 0;
}
// function to calculate the price per square inch of the pizza
double  cost_per_square_inch( double diameter, double price)
 {
     double radius, pi, area ;

     pi= 22/7;
     radius =  diameter/2 ;
     area = pi * radius * radius ;
     return(price/area);

}
