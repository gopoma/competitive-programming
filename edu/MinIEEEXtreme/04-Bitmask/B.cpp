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
    unsigned int a, b;
    cin >> a >> b;

    unsigned int ans1 = a & b;
    unsigned int ans2 = a | b;
    unsigned int ans3 = a ^ b;

    print(ans1);
    print(ans2);
    print(ans3);

    return 0;
}
