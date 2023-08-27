#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

bool isInteger(double k) {
  return floor(k) == k;
}

void solve() {
    ll a, b, c; cin >> a >> b >> c;
    double m1 = (2 * b - a) / ((double) c);
    double m2 = (a + c) / (2.0 * b);
    double m3 = (2 * b - c) / ((double) a);

    if((m1 > 0 && isInteger(m1)) || (m2 > 0 && isInteger(m2)) || (m3 > 0 && isInteger(m3))) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
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
