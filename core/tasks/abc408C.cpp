#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;

void solve() {
    ll n, m; cin >> n >> m;
    vl diff(n + 5);

    while(m--) {
        ll l, r; cin >> l >> r;
        diff[l]++;
        diff[r + 1]--;
    }

    for(int i = 1; i < n + 5; i++) {
        diff[i] += diff[i - 1];
    }

    ll re = ll(1e18) + 5;
    for(ll i = 1; i <= n; i++) {
        re = min(re, diff[i]);
    }
    cout << re << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }

    return 0;
}
