#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;

void solve() {
    ll n; cin >> n;
    vector<ll> a(n); for(auto& x: a) cin >> x;

    set<ll> b; for(auto& x: a) b.emplace(x);
    vector<ll> c; for(auto& x: b) c.emplace_back(x);

    cout << c.size() << "\n";
    for(auto& x: c) cout << x << " ";
    cout << "\n";
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
