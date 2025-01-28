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

struct FenwickTree3D {
	int n, m, l;
	vector<vector<vector<long long>>> ft;

	FenwickTree3D(vector<vector<vector<long long>>> &a) {
		n = int(a.size());
		m = int(a[0].size());
        l = int(a[0][0].size());


		ft = vector<vector<vector<long long>>>(n + 1, vector<vector<long long>>(m + 1, vector<long long>(l + 1, 0LL)));
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
                for(int k = 0; k < l; k++) {
				    update(i + 1, j + 1, k + 1, a[i][j][k]); // i + 1 -> 1-indexed, j + 1 -> 1-indexed, k + 1 -> 1-indexed
                }
			}
		}
	}

	void update(int x, int y, int z, long long val) { // 1-indexed, O(logn)
		for(int i = x; i <= n; i += (-i) & i) {
			for(int j = y; j <= m; j += (-j) & j) {
                for(int k = z; k <= l; k += (-k) & k) {
				    ft[i][j][k] += val;
                }
			}
		}
	}

	long long query(int x, int y, int z) { // 1-indexed, O(logn)
		long long res = 0LL;
		for(int i = x; i > 0; i &= i - 1) {
			for(int j = y; j > 0; j &= j - 1) {
                for(int k = z; k > 0; k &= k - 1) {
				    res += ft[i][j][k];
                }
			}
		}
		return res;
	}

	long long range_query(int x1, int y1, int z1, int x2, int y2, int z2) {
        assert(x1 <= x2 && y1 <= y2 && z1 <= z2);

        return query(x2, y2, z2)
                - query(x1 - 1, y2, z2)
                - query(x2, y1 - 1, z2)
                - query(x2, y2, z1 - 1)
                + query(x1 - 1, y1 - 1, z2)
                + query(x2, y1 - 1, z1 - 1)
                + query(x1 - 1, y2, z1 - 1)
                - query(x1 - 1, y1 - 1, z1 - 1);
	}
};

void solve() {
    int n;
    cin >> n;

    vector<vector<vector<long long>>> a(n, vector<vector<long long>>(n, vector<long long>(n, 0LL)));

    FenwickTree3D tree(a);

    int m;
    while(cin >> m) {
        assert(1 <= m && m <= 3);
        if(m == 3) break;

        if(m == 1) {
            int x, y, z;
            ll k;
            cin >> x >> y >> z >> k;

            x++; y++; z++;

            tree.update(x, y, z, k);
        } else if(m == 2) {
            int x1, y1, z1, x2, y2, z2;
            cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            x1++; y1++; z1++;
            x2++; y2++; z2++;

            ll ans = tree.range_query(x1, y1, z1, x2, y2, z2);
            cout << ans << n_l;
        } else {
            assert(false);
        }
    }
}

int main() {
    freopen("stars.in", "r", stdin);
    freopen("stars.out", "w", stdout);

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t = 1LL;
    // cin >> t;

    while(t--)
        solve();

    return 0;
}
