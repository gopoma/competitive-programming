#include <iostream>
#include <string>

using namespace std;

signed main() {
    srand (time(NULL));

    const int n = 10;
    cout << n << "\n";

    for(int i = 0; i < n; i++) {
        string partial = "";
        for(int j = 0; j < 1e6; j++) {
            partial += to_string(rand() % 10);
        }
        cout << partial << "\n";
    }

    return 0;
}
