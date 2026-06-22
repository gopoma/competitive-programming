#include <bits/stdc++.h>
using namespace std;
signed main() {
    int t = 1;
    int n = int(1e5);
    int m = n;

    int t1 = 1, t2 = int(1e9 - 500), t0 = int(1e9);

    cout << t << "\n";
    cout << n << " " << m << "\n";
    cout << t0 << " " << t1 << " " << t2 << "\n";
    for(int i = 0; i < m; i++) {
        int u = i + 1;
        int v = u + 1;
        if(v > n) v -= n;
        int l1 = 20000;
        int l2 = 2000000;
        cout << u << " " << v << " " << l1 << " " << l2 << "\n";
    }
}
