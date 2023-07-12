#include <iostream>

using namespace std;

int main() {
    
    // for(int i = 4; i>=0; i--){
    //     cout << " ";
    // }
    int n;
    cout << "Enter n: ";
    cin >> n;

    for(int i = n; i>=0; i--){
        for(int j = 1; j<=i; j++){
            cout << " ";
        }
        for(int j = 1; j<=n-i; j++){
            cout << n-i << " ";
        }
        cout << "\n";
    }

    return 0;
}
