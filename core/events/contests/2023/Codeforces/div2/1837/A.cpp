#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

void solve() {
    ll x, k;
    cin >> x >> k;

    if(k > x || (x % k != 0)) {
        cout << 1 << "\n";
        cout << x << "\n";
    } else {
        cout << 2 << "\n";
        cout << (x - 1) << " " << 1 << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t; cin >> t;

    while(t--)
        solve();

    return 0;
}
