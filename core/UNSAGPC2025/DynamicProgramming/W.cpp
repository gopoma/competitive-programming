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
    int n, k; cin >> n >> k;
    vector<int> a(n); for(auto& x: a) cin >> x;

    auto query = [&](vector<int>& pref, int l, int r) {
        if(l < 0 || r < 0 || (l >= sz(pref)) || (r >= sz(pref)) || l > r) return 0;

        int sum = pref[r];
        if(sum >= MOD) sum -= MOD;

        if(0 <= l - 1) sum -= pref[l - 1];
        if(sum < 0) sum += MOD;

        return sum;
    };

    vector<int> dp(k + 1);
    vector<int> ndp(k + 1);
    for(int i = n; i >= 0; i--) {
        for(int sum = 0; sum <= k; sum++) {
            if(i == n) {
                if(sum == k) {
                    dp[sum] = 1;
                }
            } else {
                // [sum + 0, sum + a[i]]
                int L = sum;
                int R = L + a[i];
                L = max(L, 0);
                R = min(R, k);

                dp[sum] = query(ndp, L, R);
            }

            if(1 <= sum) {
                dp[sum] += dp[sum - 1];
                if(dp[sum] >= MOD) dp[sum] -= MOD;
            }
        }

        swap(dp, ndp);
    }

    int res = query(ndp, 0, 0);
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
