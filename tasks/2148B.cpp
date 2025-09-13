#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;
using pl = pair<ll, ll>;
using vpl = vector<pl>;

void solve() {
    ll n, m, x, y; cin >> n >> m >> x >> y;
    vl a(n), b(m);
    for(auto& x: a) cin >> x;
    for(auto& x: b) cin >> x;
    ll re = n + m;
    cout << re << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;

    while(t--) {
        solve();
    }

    return 0;
}
