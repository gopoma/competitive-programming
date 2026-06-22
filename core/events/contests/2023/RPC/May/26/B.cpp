#include <bits/stdc++.h>

#define F first
#define S second

using namespace std;

using ll = long long;
using ld = long double;

void solve() {
    ll n, k;
    cin >> n >> k;

    vector<ll> a(n);

    for(ll i = 0; i < n; i++) {
        cin >> a[i];
    }



    vector<ll> s;

    for(ll tmp: a) {
        s.push_back(tmp);
    }

    sort(s.begin(), s.end());



    unordered_map<ll, ll> positions;
    for(ll i = 0; i < n; i++) {
        positions[s[i]] = i;
    }



    ll D = 0 - positions[a[0]];

    for(ll i = 1; i < n; i++) {
        D = max(D, i - positions[a[i]]);
    }

    cout << ceil(D / ((ld)(k - 1))) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
