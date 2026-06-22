#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

void solve() {
    string s; cin >> s;

    string result = "";
    char tmp = '0';

    for(ll i = 0; i < s.size(); i++) {
        if(s[i] == '?') {
            result += tmp;
        } else {
            tmp = s[i];
            result += tmp;
        }
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
