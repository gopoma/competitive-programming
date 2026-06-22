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
#define all(x)  x.begin(), x.end()
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

    for(int i = 0; i < int(v.size()); i++) {
        if (i > 0) os << " ";
        os << v[i];
    }
    return os << "]";
}

// Verification:
// * https://www.spoj.com/problems/FENTREE/
// * [F] https://redprogramacioncompetitiva.com/contests/2023/07/team/problem.php
tcT> struct SegTree {
    // LLONG_MAX is the best choice
    const T ID{(1LL<<57LL) - 1LL}; // cmb(ID,b) = b
    T cmb(T a, T b) { return a & b; }

    int n;
    V<T> seg;

    void init(int _n) { // upd, query also work if n = _n
        for (n = 1; n < _n;)
            n *= 2;
        seg.assign(2 * n, ID);
    }
    void pull(int p) {
        seg[p] = cmb(seg[2 * p], seg[2 * p + 1]);
    }
    void upd(int p, T val) { // set val at position p
        seg[p += n] = val;
        for (p /= 2; p; p /= 2)
            pull(p);
    }
    T query(int l, int r) { // zero-indexed, inclusive
        T ra = ID, rb = ID;
        for(l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1)
                ra = cmb(ra, seg[l++]);
            if (r & 1)
                rb = cmb(seg[--r], rb);
        }
        return cmb(ra, rb);
    }
    /// int first_at_least(int lo, int val, int ind, int l, int r) { // if seg stores max across range
    /// 	if (r < lo || val > seg[ind]) return -1;
    /// 	if (l == r) return l;
    /// 	int m = (l+r)/2;
    /// 	int res = first_at_least(lo,val,2*ind,l,m); if (res != -1) return res;
    /// 	return first_at_least(lo,val,2*ind+1,m+1,r);
    /// }
};

SegTree<ll> tree;

void solve() {
    int n;
    cin >> n;

    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    tree.init(n + 1);

    for(int i = 1; i <= n; i++) {
        tree.upd(i, a[i]);
    }

    int q;
    cin >> q;

    vector<int> res;
    for(int _ = 0; _ < q; _++) {
        int l; ll k; // l should be static!
        cin >> l >> k;

        if(tree.query(l, l) < k) {
            res.eb(-1LL);
        } else if(tree.query(l, n) >= k) {
            res.eb(n);
        } else {
            assert(n >= 2);

            // left is always good
            // right is always bad
            int left = l, right = n;
            while(left + 1 < right) {
                int middle = (left + right) / 2;
                assert(l <= middle && middle <= n);

                if(tree.query(l, middle) >= k) {
                    left = middle;
                } else {
                    right = middle;
                }
            }

            ll query_res = left;
            res.emplace_back(query_res);
        }
    }

    assert(sz(res) == q);
    for(int i = 0; i < q; i++) {
        cout << res[i] << " \n"[i == q - 1];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // const ll x = (1LL<<29LL) - 1;

    // DBG(x);
    // for(int i = 63; i >= 0; i--) {
    //     if (x & (1LL<<i)) cout << "1";
    //     else cout << "0";
    // }

    ll t = 1LL;
    cin >> t;

    while(t--)
        solve();

    return 0;
}
