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

bool vis[(1 << 15) + 1][15 + 1];
int memo[(1 << 15) + 1][15 + 1];

void solve() {
    int n, m; cin >> n >> m;
    using Edge = tuple<int, int, int>;

    vector<Edge> edges(m);
    for(auto& [u, v, d]: edges) {
        cin >> u >> v >> d;
    }

    vector<vector<pair<int, int>>> adj(n);
    for(auto& [u, v, d]: edges) {
        adj[u].emplace_back(v, d);
    }

    auto dp = [&](auto&& dp, int mask, int src) -> int {
        if(vis[mask][src]) return memo[mask][src];
        vis[mask][src] = true;

        int res = INF;

        for(auto& [nxt, d]: adj[src]) {
            if(mask & (1 << nxt)) {
                if(nxt == 0 && (__builtin_popcount(mask) == n)) {
                    res = min(res, d);
                } else {
                    continue;
                }
            }

            res = min(res, dp(dp, mask | (1 << nxt), nxt) + d);
        }

        return memo[mask][src] = res;
    };
    int res = dp(dp, 1, 0);
    if(res >= INF) res = -1;
    cout << res << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1; //* cin >> t;
    while(t--) {
        solve();
    }

    return 0;
}
