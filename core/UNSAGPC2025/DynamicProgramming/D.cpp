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

void solve() {
    int n; cin >> n;

    vector a(n, vector(n, vector(n, 0)));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                cin >> a[i][j][k];
            }
        }
    }

    vector sum(n + 1, vector(n + 1, vector(n + 1, 0LL)));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                sum[i + 1][j + 1][k + 1] =
                    sum[i][j + 1][k + 1] + sum[i + 1][j][k + 1] +
                    sum[i + 1][j + 1][k] - sum[i][j][k + 1] - sum[i][j + 1][k] -
                    sum[i + 1][j][k] + sum[i][j][k] + a[i][j][k];
            }
        }
    }

    auto query = [&](int lx, int rx, int ly, int ry, int lz, int rz) -> int {
        lx--, ly--, lz--;
        int res = sum[rx][ry][rz] - sum[lx][ry][rz] - sum[rx][ly][rz] -
                    sum[rx][ry][lz] + sum[lx][ly][rz] + sum[lx][ry][lz] +
                    sum[rx][ly][lz] - sum[lx][ly][lz];
        return res;
    };

    int res = -INF;
    for(int lx = 1; lx <= n; lx++) {
        for(int rx = lx; rx <= n; rx++) {
            for(int ly = 1; ly <= n; ly++) {
                for(int ry = ly; ry <= n; ry++) {
                    for(int lz = 1; lz <= n; lz++) {
                        for(int rz = lz; rz <= n; rz++) {
                            res = max(res, query(lx, rx, ly, ry, lz, rz));
                        }
                    }
                }
            }
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
