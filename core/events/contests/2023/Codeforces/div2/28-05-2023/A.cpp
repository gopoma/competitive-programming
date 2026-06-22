#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

const char nl = '\n';

void solve() {
    ll n; cin >> n;
    ll arr[n];

    for(ll& a: arr)
        cin >> a;

    for(ll& a: arr)
        cout << (n + 1 - a) << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t; cin >> t;

    while(t--)
        solve();

    return 0;
}
