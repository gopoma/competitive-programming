#include <bits/stdc++.h>

using namespace std;

void print(unsigned int x) {
    for (int i = 31; i >= 0; i--) {
        if (x&(1<<i)) cout << "1";
        else cout << "0";
    }
    cout << "\n";
}

signed main() {
    unsigned int n;
    cin >> n;

    print(n);

    unsigned int inversion = ~n;
    unsigned int logicalLeftShift = n << 1;
    unsigned int logicalRightShift = n >> 1;

    print(inversion);
    print(logicalLeftShift);
    print(logicalRightShift);
}
