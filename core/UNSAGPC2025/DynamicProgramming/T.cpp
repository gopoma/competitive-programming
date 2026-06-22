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
    vector<str> S(n); for(auto& x: S) cin >> x;

    auto check = [&](int i, int j) -> bool {
        return (0 <= i && i < n) && (0 <= j && j < m);
    };

    vector<vector<int>> dp(n, vector<int>(m));
    dp[0][0] = 1;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(S[i][j] != '.') continue;

            if(check(i - 1, j) && S[i - 1][j] == '.') {
                dp[i][j] += dp[i - 1][j];
                dp[i][j] %= MOD;
            }
            if(check(i, j - 1) && S[i][j - 1] == '.') {
                dp[i][j] += dp[i][j - 1];
                dp[i][j] %= MOD;
            }
        }
    }

    cout << dp[n - 1][m - 1] << "\n";
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
