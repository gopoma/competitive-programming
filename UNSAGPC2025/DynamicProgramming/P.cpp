#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using Matrix = pair<ll, ll>;

const ll BIG = ll(1e18);

bool vis[100 + 1][100 + 1];
ll  memo[100 + 1][100 + 1];

void solve() {
    int n; cin >> n;
    vector<Matrix> M(n);
    for(auto& [r, c]: M) cin >> r >> c;

    auto dp = [&](auto&& dp, int L, int R) -> ll {
        if(L == R) return 0;

        if(vis[L][R]) return memo[L][R];
        vis[L][R] = true;

        auto [lr, lc] = M[L];
        auto [rr, rc] = M[R];

        ll res = BIG;
        for(int i = L; i + 1 <= R; i++) {
            auto [r, c] = M[i];

            res = min(res, lr * c * rc
                + dp(dp, L, i)
                + dp(dp, i + 1, R)
            );
        }

        return memo[L][R] = res;
    };

    ll res = dp(dp, 0, n - 1);
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
