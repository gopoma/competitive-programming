#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

const ll limiter = 10e8 + 7;

void solve() {
    ll n; cin >> n;
    ll a[n], b[n];

    for(auto &aa: a)
        cin >> aa;

    for(auto &bb: b)
        cin >> bb;

    sort(a, a + n);
    sort(b, b + n);

    for(ll i = 0; i < n; i++) {
        if(b[i] >= a[i]) {
            cout << 0 << "\n";
            return;
        }
    }

    ll result = 1;
    for(ll i = 0; i < n - 1; i++) {
        result = ((result % limiter) * (lower_bound(b, b + n, a[i]) - b - i) % limiter) % limiter;
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
