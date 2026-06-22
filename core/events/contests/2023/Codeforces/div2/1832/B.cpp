#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

const char newline = '\n';

void solve() {
    ll n, k;
    cin >> n >> k;

    ll a[n];

    for(ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a, a + n);

    ll pp[n + 1];
    pp[0] = 0;
    for(ll i = 0; i < n; i++) {
        pp[i + 1] = a[i] + pp[i];
    }

    ll result = 0;
    for(ll i = 0; i <= k; i++) {
        // i represents the number of operations that consists of deleting two minimums
        result = max(result, pp[n - k + i] - pp[2 * i]);
    }

    cout << result << newline;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t; cin >> t;

    while(t--)
        solve();

    return 0;
}
