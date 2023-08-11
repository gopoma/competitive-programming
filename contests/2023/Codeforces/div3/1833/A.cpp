#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

void solve() {
    ll n;
    cin >> n;

    string s;
    cin >> s;

    unordered_set<string> tmp;

    for(ll i = 0; i < s.size() - 1; i++) {
        string current = s.substr(i, 2);
        tmp.insert(current);
    }

    cout << tmp.size() << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t;
    cin >> t;

    while(t--) {
        solve();
    }

    return 0;
}
