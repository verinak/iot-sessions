#include <iostream>

using namespace std;
//abstract class by using pure virtual functions
//objects of the Shape class cannot be instantiated directly, but it can be used as a base class for other classes
class Shape{
public:
    float area;
    //functions to be overridden by derived classes
    virtual void findArea()=0;
    virtual void display()=0;

};
//inheritence from the Shape class
class Circle: public Shape{
    float r;
    //a constructor that takes a float parameter rayon and initializes the r
public:
    Circle(float rayon){
      r=rayon;
    }
    //override functions in base class
    void findArea(){
       area= 3.14*r*r;
    }
    void display(){
       cout<<"\n\tRadius : "<< r;
       cout<<"\n\tArea : "<<area;
    }
};
class Rectangle: public Shape{
    float length, breadth;
public:
    Rectangle(float longeur, float largeur){
      length= longeur;
      breadth= largeur;
    }
    void findArea(){
       area= length*breadth;
    }
    void display(){
       cout<<"\n\tlength : "<< length;
       cout<<"\n\tbreadth : "<<breadth;
       cout<<"\n\tArea : "<<area;
    }
};
class Triangle: public Shape{
    float height, base;
public:
    Triangle(float h, float b){
      height= h;
      base= b;
    }
    void findArea(){
       area= (height*base)/2;
    }
    void display(){
       cout<<"\n\theight : "<< height;
       cout<<"\n\tbase : "<<base;
       cout<<"\n\tArea : "<<area;
    }
};
int main()
{
    Shape *obj; // Declare a pointer to the Shape base class
    char letter; // Variable to store the user's choice of shape
    bool cont = true; // Boolean variable to control the program loop

do {
         // Display shape options to the user
    cout << "This program displays the area of the following shapes: " << endl;
    cout << "Write c for a circle." << endl;
    cout << "Write r for a rectangle." << endl;
    cout << "Write t for a triangle." << endl;
    cout << "Enter your choice: ";

    cin >> letter;

    switch (letter) {
        case 'c':
        case 'C': {
            float n;
            char le;
            cout << "Enter radius of the circle: ";
            cin >> n;
            Circle c1(n);  // Create a Circle object with the given radius
            obj = &c1;  // Assign the address of the Circle object to the Shape pointer
            cout << "Circle: ";
            obj->findArea();  // Call the findArea() function of the Circle object through the Shape pointer
            obj->display();
            cout << "\nDo you want to continue? (Y/N) ";
            cin >> le;
            if (le == 'N' || le == 'n') {
                cont = false; // Set the loop control variable to exit the loop
            }
            break;
        }
        case 'r':
        case 'R': {
             float l,b;
        char le;
        cout<<"\nEnter length of the rectangle : ";
        cin>>l;
        cout<<"\nEnter breadth of the rectangle : ";
        cin>>b;
        Rectangle r1(l, b);
        obj=&r1;
        cout<<"\nRectangle: ";
        obj->findArea();
        obj->display();
        cout<<"\nDo you want to continue? (Y/N) ";
        cin>>le;
        if(le== 'N' || le== 'n'){
          cont =false;
         }
        else{
          cont=true;
         }
            break;
        }
        case 't':
        case 'T': {
            float h,b;
        char le;
        cout<<"\nEnter height of the triangle : ";
        cin>>h;
        cout<<"\nEnter base of the triangle : ";
        cin>>b;
        Triangle t1(h, b);
        obj=&t1;
        cout<<"\nTriangle: ";
        obj->findArea();
        obj->display();
        cout<<"\nDo you want to continue? (Y/N) ";
        cin>>le;
        if(le== 'N' || le== 'n'){
         cont =false;
        }
        else{
         cont=true;
        }
            break;
        }
    }
} while (cont);  // Repeat the loop as long as cont is true
cout<<"\nThe program has ended";
return 0;
}

