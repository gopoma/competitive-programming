//* sometimes pragmas don't work, if so, just comment it!
#pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

//! #undef _GLIBCXX_DEBUG //? for Stress Testing

#include <bits/stdc++.h>
using namespace std;

//* Debugger
string to_string(string s) {
    return '"' + s + '"';
}

string to_string(const char* s) {
    return to_string((string) s);
}

string to_string(char c) {
    return string(1, c);
}

string to_string(bool b) {
    return (b ? "true" : "false");
}

template <typename A>
string to_string(A v);

string to_string(vector<bool> v) {
    bool first = true;
    string res = "[";
    for (auto x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += x ? "true" : "false";
    }
    res += "]";
    return res;
}

template <typename A, typename B>
string to_string(pair<A, B> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}


template <typename A>
string to_string(A v) {
    bool first = true;
    string res = "[";
    for (const auto &x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(x);
    }
    res += "]";
    return res;
}

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}

#ifdef LOCAL
#define MACRO(code) do {code} while (false)
#define dbg(x)      {auto xd = x; cout << "Line(" << __LINE__ << "): " << "\033[1;34m" << #x << "\033[0;32m = \033[35m" << to_string(xd) << "\033[0m" << endl;}
#define dbg(...)    MACRO(cout << "Line(" << __LINE__ << "): " << "\033[1;34m" << "[" << #__VA_ARGS__ << "]\033[35m:"; debug_out(__VA_ARGS__); cout << "\033[0m";)

#define GA          dbg(0)
#define RAYA        cout << "\033[101m" << "================================" << "\033[0m" << endl;
#else
#define dbg(x)
#define dbg(...)
#define GA
#define RAYA
#endif
//* /Debugger

using ll = long long;
using db = long double; // or double if tight TL
using str = string;

using pi = pair<int,int>;
using pl = pair<ll, ll>;
#define f first
#define s second

#define tcT template<class T
tcT> using V = vector<T>;
tcT, size_t SZ> using AR = array<T,SZ>;
using vi = V<int>;
using vl = V<ll>;
using vb = V<bool>;
using vpi = V<pi>;

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

const int MOD = 1e9+7;
const db PI = acos((db)-1);
mt19937 rng(0); // or mt19937_64
//* mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

tcT> bool ckmin(T& a, const T& b) {
	return b < a ? a = b, 1 : 0; } // set a = min(a,b)
tcT> bool ckmax(T& a, const T& b) {
	return a < b ? a = b, 1 : 0; } // set a = max(a,b)

void setIn(string s) { freopen(s.c_str(), "r", stdin); }

const auto beg_time = std::chrono::high_resolution_clock::now();
// https://stackoverflow.com/questions/47980498/accurate-c-c-clock-on-a-multi-core-processor-with-auto-overclock?noredirect=1&lq=1
double time_elapsed() {
	return chrono::duration<double>(std::chrono::high_resolution_clock::now() -
	                                beg_time)
	    .count();
}

const ll BIG = ll(1e18);

//* Template
/**
 * Description: A set (not multiset!) with support for finding the $n$'th
   * element, and finding the index of an element. Change \texttt{null\_type} to get a map.
 * Time: O(\log N)
 * Source: KACTL
   * https://codeforces.com/blog/entry/11080
 * Verification: many
 */

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
tcT> using Tree = tree<T, null_type, less<T>,
	rb_tree_tag, tree_order_statistics_node_update>;
#define ook order_of_key
#define fbo find_by_order

void treeExample() {
	//* Tree<int> t, t2; t.insert(8);
	//* auto it = t.insert(10).f; assert(it == t.lb(9));
	//* assert(t.ook(10) == 1 && t.ook(11) == 2 && *t.fbo(0) == 8);
	//* t.join(t2); // assuming T < T2 or T > T2, merge t2 into t
}

/**
int atMost(Tree<pi>& T, int r) {
	return T.ook({r,MOD}); }
int getSum(Tree<pi>& T, int l, int r) {
	return atMost(T,r)-atMost(T,l-1); }
*/
//* /Template

/**
 * Description: 1D point update and range query where \texttt{cmb} is
 	* any associative operation. \texttt{seg[1]==query(0,N-1)}.
 * Time: O(\log N)
 * Source:
	* http://codeforces.com/blog/entry/18051
	* KACTL
 * Verification: SPOJ Fenwick
 * API: SegTree<node> tree; tree.init(int(n));
 */

tcT> struct SegTree { // cmb(ID,b) = b
	// const T ID{}; T cmb(T a, T b) { return a+b; }
    T ID{-BIG}; T cmb(T a, T b) { return max(a, b); }
	int n; V<T> seg;
	void init(int _n) { // upd, query also work if n = _n
		for (n = 1; n < _n; ) n *= 2;
		seg.assign(2*n,ID); }
	void pull(int p) { seg[p] = cmb(seg[2*p],seg[2*p+1]); }
	void upd(int p, T val) { // set val at position p
		seg[p += n] = val; for (p /= 2; p; p /= 2) pull(p); }
	T query(int l, int r) {	// zero-indexed, inclusive
		T ra = ID, rb = ID;
		for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
			if (l&1) ra = cmb(ra,seg[l++]);
			if (r&1) rb = cmb(seg[--r],rb);
		}
		return cmb(ra,rb);
	}
	/// int first_at_least(int lo, int val, int ind, int l, int r) { // if seg stores max across range
	/// 	if (r < lo || val > seg[ind]) return -1;
	/// 	if (l == r) return l;
	/// 	int m = (l+r)/2;
	/// 	int res = first_at_least(lo,val,2*ind,l,m); if (res != -1) return res;
	/// 	return first_at_least(lo,val,2*ind+1,m+1,r);
	/// }
};

/**
 * Description: Hash map with similar API as unordered\_map.
 	* Initial capacity must be a power of 2 if provided.
 * Source: KACTL
 * Memory: \tilde 1.5x unordered map
 * Time: \tilde 3x faster than unordered map
 * API: hash_map<ll, ll> go({},{},{},{}, {1 << 20});
 */

// #include<bits/extc++.h>
#include <ext/pb_ds/assoc_container.hpp>

//? For CodeForces, or other places where hacking might be a problem:

const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct custom_hash {
	static uint64_t splitmix64(uint64_t x) {
		// http://xorshift.di.unimi.it/splitmix64.c
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}

	size_t operator()(pair<uint64_t,uint64_t> x) const {
		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x.first + FIXED_RANDOM)^(splitmix64(x.second + FIXED_RANDOM) >> 1);
	}
};
struct chash { // To use most bits rather than just the lowest ones:
	const uint64_t C = ll(4e18 * acos(0)) | 71; // large odd number
	ll operator()(ll x) const { return __builtin_bswap64((x^RANDOM)*C); }
};
//?__gnu_pbds::gp_hash_table<ll, int, chash> h({},{},{},{}, {1 << 16});

template <typename K, typename V, typename Hash = chash>
using hash_map = __gnu_pbds::gp_hash_table<K, V, Hash>;

template <typename K, typename Hash = chash>
using hash_set = hash_map<K, __gnu_pbds::null_type, Hash>;

// /here goes the template!

void solve() {
    // <>
    ll n, tar_sum, tar_mx; cin >> n >> tar_sum >> tar_mx;
    vl a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }



    vl pref = a;
    for(int i = 1; i <= n; i++) {
        pref[i] += pref[i - 1];
    }
    dbg(n, tar_sum, tar_mx);
    dbg(a);
    dbg(pref);



    set<ll> where_tar_mx;
    for(int i = 1; i <= n; i++) {
        if(a[i] == tar_mx) {
            where_tar_mx.emplace(i);
        }
    }

    SegTree<ll> st_mx; st_mx.init(n + 5);
    for(int i = 1; i <= n; i++) {
        st_mx.upd(i, a[i]);
    }

    hash_map<ll, Tree<ll>> mp;
    for(int i = 0; i <= n; i++) {
        mp[pref[i]].insert(i);
    }
    dbg(where_tar_mx);



    ll res = 0;
    for(int i = 1; i <= n; i++) {
        RAYA;
        dbg(i);
        // check if there's x
        ll lst_tar_mx_idx = -1;
        {
            auto it = where_tar_mx.upper_bound(i);
            if(it == where_tar_mx.begin()) {
                dbg("bad 1");
                continue;
            }
            it--;
            lst_tar_mx_idx = *it;
        }
        assert(lst_tar_mx_idx != -1);

        // check last greater than x
        ll lst_gt_tar_mx_idx = 0;
        if(st_mx.query(0, i) > tar_mx) {
            ll left = 0; // always good
            ll right = i + 1; // always bad
            while(left + 1 < right) {
                ll middle = (left + right) >> 1LL;
                if(st_mx.query(middle, i) > tar_mx) left = middle;
                else right = middle;
            }
            lst_gt_tar_mx_idx = left;
        }

        dbg(":v",lst_gt_tar_mx_idx, lst_tar_mx_idx);

        if(lst_tar_mx_idx <= lst_gt_tar_mx_idx) {
            dbg("bad 2");
        }

        // [lst_gt_tar_mx_idx, lst_tar_mx_idx]
        // pref[i] - pref[j] = tar_sum
        // pref[j] = pref[i] - tar_sum
        lst_gt_tar_mx_idx;
        lst_tar_mx_idx--;
        ll tar_pref = pref[i] - tar_sum;
        dbg(lst_gt_tar_mx_idx, lst_tar_mx_idx, tar_pref);
        {
            auto it = mp[tar_pref].lower_bound(lst_gt_tar_mx_idx);
            if(mp[tar_pref].empty() || ((*it) > lst_tar_mx_idx)) {
                continue;
            }
        }
        {
            auto it_r = mp[tar_pref].upper_bound(lst_tar_mx_idx);
            if(it_r == mp[tar_pref].begin()) continue;
            it_r--;

            auto it_l = mp[tar_pref].lower_bound(lst_gt_tar_mx_idx);
            if(it_l == mp[tar_pref].end()) continue;

            ll L = ll(mp[tar_pref].ook(*it_l));
            ll R = ll(mp[tar_pref].ook(*it_r));
            dbg(mp[tar_pref], L, R);
            ll contrib =  R - L + 1LL;
            dbg(contrib);
            res += contrib;
        }
    }
    dbg(res);
    cout << res << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    {
        Tree<ll> st;
        st.insert(2LL);
        st.insert(6LL);
        st.insert(8LL);
        dbg(st.ook(2LL));
        dbg(st.ook(6LL));
        dbg(st.ook(8LL));
        dbg(*st.fbo(0));
        dbg(*st.fbo(1));
        dbg(*st.fbo(2));
    }

    int t = 1; cin >> t;
    while(t--) {
        RAYA;
        RAYA;
        RAYA;
        RAYA;
        solve();
    }

    #ifdef LOCAL
        cerr << fixed << setprecision(5);
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
        cerr << "\033[42mtime = " << time_elapsed() << "ms\033[0m\n";
        cerr << "\033[42m++++++++++++++++++++\033[0m";
    #endif
}
