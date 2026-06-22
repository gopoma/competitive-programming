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

using InputItem = tuple<int, int, int>;
using Item = pair<int, int>;
void solve() {
    //* <>
    int n, W; cin >> n >> W;
    vector<InputItem> a(n);
    for(auto& [v, w, m]: a) cin >> v >> w >> m;

    vector<Item> items;

    for(int i = 0; i < n; i++) {
        auto [v, w, m] = a[i];
        int c = 1, k;

        k = m;
        while (k > c) {
            k -= c;

            Item current;
            current.first  = c * w;
            current.second = c * v;

            items.emplace_back(current);

            c *= 2;
        }

        Item current;
        current.first  = w * k;
        current.second = v * k;

        items.emplace_back(current);
    }

    const int N = sz(items);
    vector<vector<int>> dp(N + 1, vector<int>(W + 1, -INF));

    for(int i = N; i >= 0; i--) {
        for(int C = 0; C <= W; C++) {
            if(i == N) {
                dp[i][C] = 0;
                continue;
            }

            auto [w, v] = items[i];

            //* no take
            dp[i][C] = max(dp[i][C], dp[i + 1][C]);

            //* take
            if(C + w <= W) {
                dp[i][C] = max(dp[i][C], dp[i + 1][C + w] + v);
            }
        }
    }

    int response = dp[0][0];
    cout << response << "\n";
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
