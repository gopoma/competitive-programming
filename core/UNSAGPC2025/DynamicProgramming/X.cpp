#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll BIG = ll(1e18);

bool vis[400 + 1][400 + 1];
ll  memo[400 + 1][400 + 1];

void solve() {
    int n; cin >> n;
    vector<ll> a(n);
    for(auto& x: a) cin >> x;

    auto dp = [&](auto&& dp, int l, int r) -> ll {
        if(l == r) return 0;

        if(vis[l][r]) return memo[l][r];
        vis[l][r] = true;

        ll res = BIG;
        ll tot = 0;
        for(int i = l; i <= r; i++) {
            tot += a[i];
        }
        for(int i = l; i + 1 <= r; i++) {
            res = min(res, tot + dp(dp, l, i) + dp(dp, i + 1, r));
        }
        return memo[l][r] = res;
    };

    ll res = dp(dp, 0, n - 1);
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
}
