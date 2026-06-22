#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;
using pl = pair<ll, ll>;
using vpl = vector<pl>;

void solve() {
    ll x, n; cin >> x >> n;

    ll re = 0;

    ll cur = x;
    for(int i = 0; i < n; i++) {
        re += x;
        x = -x;
    }
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
