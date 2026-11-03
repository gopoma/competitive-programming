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

#define lb lower_bound
#define ub upper_bound

const int MOD = (int)1e9 + 7;   // 998244353;
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

struct FenwickTree {
	int n;
	vector<long long> ft;

	FenwickTree(vector<long long> &a) {
		n = int(a.size());

		ft = vector<long long>(n + 1, 0LL);
		for(int i = 0; i < int(a.size()); i++) {
            update(i + 1, a[i]); // i + 1 -> 1-indexed
        }
	}

	void update(int pos, long long val) { // 1-indexed, O(logn)
		while(pos <= n) {
			ft[pos] += val;
			pos += (-pos) & pos;
		}
	}

	long long query(int pos) { // 1-indexed, O(logn)
		long long res = 0LL;
		while(pos > 0) {
			res += ft[pos];
			pos &= pos - 1; // ~ pos -= LSO(pos)
		}
		return res;
	}

	long long range_query(int l, int r) {
		return query(r) - query(l - 1);
	}
};

void solve() {
    int n, m;
    cin >> n >> m;

    vector<ll> a(n);
    for(auto& e: a) {
        cin >> e;
    }

    FenwickTree tree(a);

    for(int _ = 0; _ < m; _++) {
        int t;
        cin >> t;

        if(t == 0) {
            int left, right;
            cin >> left >> right;

            ll ans = tree.range_query(left, right);
            cout << ans << n_l;
        } else if(t == 1) {
            int pos;
            ll val;
            cin >> pos >> val;

            ll prev_val = tree.range_query(pos, pos);
            tree.update(pos, val - prev_val);
        } else {
            assert(false);
        }
    }
}

int main() {
    freopen("rsq.in", "r", stdin);
    freopen("rsq.out", "w", stdout);

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t = 1LL;
    // cin >> t;

    while(t--)
        solve();

    return 0;
}
