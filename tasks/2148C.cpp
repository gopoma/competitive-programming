#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;
using pl = pair<ll, ll>;
using vpl = vector<pl>;

#define dbg(x) cout << #x << ": " << x << endl;
#define dbgs(x) cout << #x << ": " << x << ", ";
#define dbg(x) 0
#define dbgs(x) 0

void solve() {
    ll n, m; cin >> n >> m;
    vl a(n), b(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }

    ll t = 0;
    ll S = 0;

    ll re = 0;
    for(int i = 0; i < n; i++) {
        if(b[i] != t) {
            ll d = a[i] - S;
            while(d % 2 == 0) d--;
            re += d;

            dbgs(i);
            dbgs(d);
        } else {
            ll d = a[i] - S;
            while(d % 2 == 1) d--;
            re += d;

            dbgs(i);
            dbgs(d);
        }
        // cout << endl;
        t = b[i];
        S = a[i];
    }

    ll queda = m - a[n - 1];
    re += queda;

    cout << re << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;

    while(t--) {
        dbg("==================================");
        solve();
    }

    return 0;
}
