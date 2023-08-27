#include <bits/stdc++.h>

#define F first
#define S second

using namespace std;

using ll = long long;

void solve() {
    ll s, n;

    cin >> s >>  n;

    vector<pair<ll, ll>> tmp;

    for(ll i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;

        tmp.push_back(make_pair(x, y));
    }

    sort(tmp.begin(), tmp.end());

    for(auto aux: tmp) {
        if(s <= aux.F) {
            cout << "NO\n";
            return;
        } else {
            s += aux.S;
        }
    }

    cout << "YES\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
