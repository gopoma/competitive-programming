#pragma GCC optimize ("Ofast")

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;
using pl = pair<ll, ll>;
using vpl = vector<pl>;

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

#define dbg(x) cout << #x << ": " << x << endl;
// #define dbg(x) 0

using Item = pair<int, int>;
bool vis[int(1e2) + 1][int(1e4) + 1];
int memo[int(1e2) + 1][int(1e4) + 1];
void solve() {
    int n, W; cin >> n >> W;
    vector<Item> a(n);
    for(auto& [v, w]: a) cin >> v >> w;

    for(int i = 0; i <= n; i++) {
        for(int C = 0; C <= W; C++) {
            vis[i][C] = false;
        }
    }

    auto dp = [&](auto&& dp, int i, int C) -> int {
        if(i == n) return 0;

        if(vis[i][C]) return memo[i][C];
        vis[i][C] = true;

        auto [v, w] = a[i];
        int res =dp(dp, i + 1, C);
        if(C + w <= W) {
            res = max(res, dp(dp, i + 1, C + w) + v);
        }

        return memo[i][C] = res;
    };

    int res = dp(dp, 0, 0);
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1; // cin >> t;
    while(t--) {
        solve();
    }

    return 0;
}
