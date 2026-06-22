#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;

#define dbg(x) cout << #x << ": " << x << endl;
// #define dbg(x) 0

void solve() {
    ll n, m; cin >> n >> m;
    vl a(n); for(auto& x: a) cin >> x;
    auto check = [&]() -> bool {
        map<ll, ll> hist;
        for(auto& x: a) hist[x]++;
        for(ll i = 1; i <= m; i++) {
            if(hist[i] == 0) return false;
        }
        return true;
    };
    ll re = 0;
    while(check()) {
        a.pop_back(); re++;
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
