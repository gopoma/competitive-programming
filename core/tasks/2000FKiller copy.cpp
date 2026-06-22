#include <bits/stdc++.h>
using namespace std;
signed main() {
    int t = 1;
    int n = 1000;
    int k = 100;
    vector<pair<int, int>> a(n, make_pair(100, 100));

    cout << t << "\n";
    cout << n << " " << k << "\n";
    for(auto& [xx, yy]: a) {
        cout << xx << " " << yy << "\n";
    }
}
