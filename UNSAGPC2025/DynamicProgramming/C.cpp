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

/**
 * Description: calculates rectangle sums in constant time
 * Source: KACTL
 * Verification: POI 16 Ticket Inspector
 */

template<class T> struct PrefixSums {
	vector<vector<T>> sum;
	void init(const vector<vector<T>>& v) {
		int R = sz(v), C = sz(v[0]);
		sum.assign(R+1,vector<T>(C+1));
		F0R(i,R) F0R(j,C)
			sum[i+1][j+1] = v[i][j]+sum[i+1][j]+sum[i][j+1]-sum[i][j];
	}
	T get(int X1, int X2, int Y1, int Y2) {
		X2 ++, Y2 ++;
		return sum[X2][Y2]-sum[X1][Y2]
			-sum[X2][Y1]+sum[X1][Y1];
	}
};

void solve() {
    int n; cin >> n;

    vector<vector<int>> a(n, vector<int>(n));
    for(auto& vec: a) for(auto& x: vec) cin >> x;

    PrefixSums<int> st; st.init(a);

    int res = -(1e9);
    for(int xl = 0; xl < n; xl++) {
        for(int xr = xl; xr < n; xr++) {
            for(int yl = 0; yl < n; yl++) {
                for(int yr = yl; yr < n; yr++) {
                    res = max(res, st.get(xl, xr, yl, yr));
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
