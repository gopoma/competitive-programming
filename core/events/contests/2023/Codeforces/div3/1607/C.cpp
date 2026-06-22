#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

void solve() {
    ll n; cin >> n;

    ll a[n];
    for(auto &aa: a)
        cin >> aa;

    if(n == 1) {
        cout << a[0] << "\n";
        return;
    }

    sort(a, a + n);

    ll result = a[0];
    ll accumulator = a[0];

    for(ll i = 1; i < n; i++) {
        result = max(result, a[i] - accumulator);
        accumulator += a[i] - accumulator;
    }

    cout << result << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t; cin >> t;

    while(t--)
        solve();

    return 0;
}
