#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;

void solve() {
    ll n, q; cin >> n >> q;
    vl a(n), b(n);
    for(auto& x: a) cin >> x;
    for(auto& x: b) cin >> x;

    ll re = 0;
    for(int i = 0; i < n; i++) {
        re += min(a[i], b[i]);
    }

    for(int _ = 0; _ < q; _++) {
        char c; cin >> c;
        ll X, V; cin >> X >> V; X--;

        re -= min(a[X], b[X]);
        if(c == 'A') {
            a[X] = V;
        } else {
            b[X] = V;
        }
        re += min(a[X], b[X]);
        cout << re << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
