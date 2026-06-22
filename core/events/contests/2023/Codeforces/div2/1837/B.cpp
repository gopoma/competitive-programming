#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

void solve() {
    ll n; cin >> n;
    string s; cin >> s;

    // <<>>
    ll result = 1, counter = 1;
    for(ll i = 1; i < n; i++) {
        if(s[i] == s[i - 1]) {
            counter++;
        } else {
            result = max(result, counter);
            counter = 1;
        }
    }
    result = max(result, counter);

    cout << (result + 1) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t; cin >> t;

    while(t--)
        solve();

    return 0;
}
