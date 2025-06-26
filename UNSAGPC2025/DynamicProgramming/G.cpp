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
void solve() {
    int n, W; cin >> n >> W;
    vector<Item> a(n);
    int sum_value = 0;
    for(auto& [v, w]: a) {
        cin >> v >> w;
        sum_value += v;
    }


    vector<vector<int>> dp(n + 1, vector<int>(sum_value + 1, INF));
    dp[0][0] = 0;
    for(int i = 0; i < n; i++) {
        auto [v, w] = a[i];
        for(int tot_value = 0; tot_value + v <= sum_value; tot_value++) {
            dp[i + 1][tot_value] = min(dp[i + 1][tot_value], dp[i][tot_value]);
            dp[i + 1][tot_value + v] = min(dp[i + 1][tot_value + v], dp[i][tot_value] + w);
        }
    }

    int res = -INF;
    for(int tot_value = 0; tot_value <= sum_value; tot_value++) {
        if(dp[n][tot_value] <= W) {
            res = max(res, tot_value);
        }
    }
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
