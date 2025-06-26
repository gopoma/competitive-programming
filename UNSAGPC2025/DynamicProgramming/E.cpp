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

void solve() {
    int n; cin >> n;
    vl p(n + 1); for(int i = 1; i <= n; i++) cin >> p[i];

    vl dp(n + 1, -BIG); dp[0] = 0;
    for(int i = 1; i <= n; i++) {
        for(int cut_size = 1; cut_size <= i; cut_size++) {
            dp[i] = max(dp[i], p[cut_size] + dp[i - cut_size]);
        }
    }

    cout << dp[n] << "\n";
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
