#include <iostream>

using namespace std;

int main() {
    
    double score1, score2, score3, avg;
    cout << "\nEnter 3 scores: ";
    cin >> score1 >> score2 >> score3;
    avg = (score1 + score2 + score3)/3;
    cout << "Average score: " << avg << "\n";
    // switch (avg) {
    //     case avg >= 90:

    //         break;
    // }

    if(avg >= 90){
        cout << "Your grade is A\n";
    }
    else if(avg >= 80){
        cout << "Your grade is B\n";
    }
    else if(avg >= 70){
        cout << "Your grade is C\n";
    }
    else if(avg >= 60){
        cout << "Your grade is D\n";
    }
    else{
        cout << "Your grade is F\n";
    }

    return 0;
}
