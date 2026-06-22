#include <bits/stdc++.h>
using namespace std;

using ll = long long;
void solve() {
    ll n, q; cin >> n >> q;
    vector<ll> a(n); for(auto& x: a) cin >> x;
    vector<pair<ll, ll>> queries(q); for(auto& [l, r]: queries) {
        cin >> l >> r;
        r--;
    }

    vector<ll> pref = a;
    for(int i = 1; i < n; i++) pref[i] += pref[i - 1];

    for(auto& [l, r]: queries) {
        ll res = pref[r];
        if(0 <= l - 1) res -= pref[l - 1];
        cout << res << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
