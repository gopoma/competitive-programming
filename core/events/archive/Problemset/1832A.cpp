#include <bits/stdc++.h>

using namespace std;

using ll = long long;

void solve() {
    string s;
    cin >> s;

    map<char, ll> tmp;

    for(char c: s) {
        tmp[c]++;
    }

    ll hasMoreThanOne = 0;

    for(auto aux: tmp) {
        if(aux.second > 1) {
            hasMoreThanOne++;
        }
    }

    if(hasMoreThanOne <= 1) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
    }
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
