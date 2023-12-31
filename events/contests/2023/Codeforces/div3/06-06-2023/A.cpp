#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

const char nl = '\n';

void solve() {
    ll n;
    cin >> n;

    string s;
    cin >> s;

    string result = "";
    char current = s[0];
    for(ll i = 1; i < n; i++) {
        if(s[i] == current) {
            result += s[i];
            if(i == n - 1) break;
            current = s[i + 1];
            i++;
        }
    }

    cout << result << nl;
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
