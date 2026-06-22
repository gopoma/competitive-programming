#pragma GCC optimize ("Ofast")

#undef _GLIBCXX_DEBUG //? for Stress Testing

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;
using pl = pair<ll, ll>;
using vpl = vector<pl>;
using str = string;

#define sz(x) int((x).size())
#define all(x) begin(x), end(x)
#define sor(x) sort(all(x))
#define rsz resize
#define pb push_back
#define ft front()
#define bk back()

#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define rep(a) F0R(_,a)
#define each(a,x) for (auto& a: x)

const ll BIG = ll(1e18);
const int INF = int(1e9);
const int MOD = int(1e9) + 7;

#define dbg(x) cout << #x << ": " << x << endl;
// #define dbg(x) 0

bool vis[1000 + 5][1000 + 5];
int memo[1000 + 5][1000 + 5];

void solve() {
    str X, Y; cin >> X >> Y;
    const int n = sz(X);
    const int m = sz(Y);

    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= m; j++) {
            vis[i][j] = false;
        }
    }
    auto dp = [&](auto&& dp, int i, int j) -> int {
        if(i == n || j == m) return 0;

        if(vis[i][j]) return memo[i][j];
        vis[i][j] = true;

        int res = 0;

        if(X[i] == Y[j]) {
            res = max(res, dp(dp, i + 1, j + 1) + 1);
        } else {
            res = max(res, dp(dp, i + 1, j));
            res = max(res, dp(dp, i, j + 1));
        }

        return memo[i][j] = res;
    };

    int res = dp(dp, 0, 0);
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1; cin >> t;
    while(t--) {
        solve();
    }

    return 0;
}
