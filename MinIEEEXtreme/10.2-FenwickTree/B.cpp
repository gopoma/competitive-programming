// sometimes pragmas don't work
#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;

#define MACRO(code) do {code} while (false)
#define DBG(x) MACRO(cerr << #x << " = " << (x) << endl;)
#define DBGY(x) MACRO(cerr << #x << " = " << (x) << " , ";)
#define DBG2(x,y) MACRO(DBGY(x); DBG(y);)
#define DBG3(x,y,z) MACRO(DBGY(x); DBGY(y); DBG(z);)
#define DBG4(x,y,z,w) MACRO(DBGY(x); DBGY(y); DBGY(z); DBG(w);)
#define RAYA MACRO(cerr << " ================ " << endl;)

#define tcT template<class T

using ll = long long;
using ld = long double;       // or double if tight TL
using u128 = __uint128_t;
using str = string;         // yay python!
tcT> using V = vector<T>;
tcT, size_t SZ> using AR = array<T, SZ>;

#define sz(x)   int((x).size())
#define all(x)  bg(x), end(x)
#define rall(x) x.rbegin(), x.rend()
#define sor(x)  sort(all(x))
#define ins     insert
#define pb      push_back
#define eb      emplace_back

const ld PI = acos((ld)-1);
mt19937 rng(0); // or mt19937_64
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};  // for every grid problem!!
const char n_l = '\n';

template <typename T>
ostream& operator <<(ostream &os, const vector<T>& v) {
    os << "[";

    for(int i = 0; i < sz(v); i++) {
        if (i > 0) os << " ";
        os << v[i];
    }
    return os << "]";
}

struct FenwickTree2D {
	int n, m;
	vector<vector<long long>> ft;

	FenwickTree2D(vector<vector<long long>> &a) {
		n = int(a.size());
		m = int(a[0].size());

		ft = vector<vector<long long>>(n + 1, vector<long long>(m + 1, 0LL));
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				update(i + 1, j + 1, a[i][j]); // i + 1 -> 1-indexed, j + 1 -> 1-indexed
			}
		}
	}

	void update(int x, int y, long long val) { // 1-indexed, O(logn)
		for(int i = x; i <= n; i += (-i) & i) {
			for(int j = y; j <= m; j += (-j) & j) {
				ft[i][j] += val;
			}
		}
	}

	long long query(int x, int y) { // 1-indexed, O(logn)
		long long res = 0;
		for(int i = x; i > 0; i &= i - 1) {
			for(int j = y; j > 0; j &= j - 1) {
				res += ft[i][j];
			}
		}
		return res;
	}

	long long range_query(int x1, int y1, int x2, int y2) {
		return query(x2, y2) + query(x1 - 1, y1 - 1) - query(x1 - 1, y2) - query(x2, y1 - 1);
	}
};

void solve() {
    int n, q;
    cin >> n >> q;

    vector<vector<ll>> A(n, vector<ll>(n, 0LL));

    FenwickTree2D tree(A);

    for(int _ = 0; _ < q; _++) {
        string operation;
        cin >> operation;

        if(operation == "ADD") {
            int x, y;
            cin >> x >> y;

            tree.update(x, y, 1LL);
        } else if(operation == "GET") {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;

            ll ans = tree.range_query(x1, y1, x2, y2);
            cout << ans << n_l;
        } else {
            assert(false);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t = 1LL;
    // cin >> t;

    while(t--)
        solve();

    return 0;
}
