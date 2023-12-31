#include <iostream>

using namespace std;

int main() {
    cout << "1\n";
    cout << "200000\n";
    for(int i = 0; i < 199999; i++) {
        cout << "2 ";
    }
    cout << "2\n";

    return 0;
}