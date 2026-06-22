#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

void solve() {
    ll x, n;
    cin >> x >> n;

    if(n == 0) {
        cout << x << "\n";
        return;
    }

    bool isEven = x % 2 == 0;

    ll increment;

    if(n % 4 == 0) {
        increment = 0;
    } else if(n % 4 == 1) {
        increment = (-4 * floor(n / 4.0)) - 1;
    } else if(n % 4 == 2) {
        increment = 1;
    } else {
        increment = (4 * ceil(n / 4.0));
    }

    if(!isEven) {
        increment *= -1;
    }

    cout << (x + increment) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t; cin >> t;

    while(t--)
        solve();

    return 0;
}
