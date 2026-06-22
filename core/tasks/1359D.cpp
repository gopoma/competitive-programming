#include <bits/stdc++.h>
using namespace std;



#ifdef LOCAL
    #include "debug.h"
#else
    #define dbg(...)     0
    #define chk(...)     0

    #define RAYA         0
#endif



const auto beg_time = std::chrono::high_resolution_clock::now();
double time_elapsed() { return chrono::duration<double>(std::chrono::high_resolution_clock::now() - beg_time) .count(); }



// building blocks
using ll  = long long;
using db  = long double;
using str = string;

//? priority_queue for minimum
template<class T> using pqg = priority_queue<T, vector<T>, greater<T>>;
 
using ull  = unsigned long long;
//? using i64  = long long;
//? using u64  = uint64_t;
//? using i128 = __int128;
//? using u128 = __uint128_t;
//? using f128 = __float128;



// pairs
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<db, db>;

#define mp make_pair
#define f  first
#define s  second



#define tcT template <class T
#define tcTU tcT, class U

tcT > using V = vector<T>;
tcT, size_t SZ > using AR = array<T, SZ>;
using vi = V<int>;
using vb = V<bool>;
using vl = V<ll>;
using vd = V<db>;
using vs = V<str>;
using vpi = V<pi>;
using vpl = V<pl>;
using vpd = V<pd>;

// vectors
// oops size(x), rbegin(x), rend(x) need C++17
#define sz(x) int((x).size())
#define bg(x) begin(x)
#define all(x) bg(x), end(x)
#define rall(x) x.rbegin(), x.rend()
#define sor(x) sort(all(x))
#define rsz resize
#define ins insert
#define pb push_back
#define eb emplace_back
#define ft front()
#define bk back()
#define ts to_string

#define lb lower_bound
#define ub upper_bound



// loops
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define rep(a) F0R(_, a)
#define each(a, x) for (auto &a : x)



// Pocochuk Adapter
using vvi = V<vi>;
using vvl = V<vl>;
using vvb = V<vb>;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pi;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<bool> vb;
typedef vector<vb> vvb;



tcT > bool ckmin(T &a, const T &b) {
	return b < a ? a = b, 1 : 0;
}  // set a = min(a,b)
tcT > bool ckmax(T &a, const T &b) {
	return a < b ? a = b, 1 : 0;
}  // set a = max(a,b)

//? Template
const ll BIG = ll(1e18);
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


ll cdiv(ll a, ll b) {
	return a / b + ((a ^ b) > 0 && a % b);
}  // divide a by b rounded up
ll fdiv(ll a, ll b) {
	return a / b - ((a ^ b) < 0 && a % b);
}  // divide a by b rounded down

// /here goes the template!
//? /Template

ll brute(ll n, vl a) {
    ll ans = -BIG;
    for(int L = 0; L < n; L++) {
        for(int R = L; R < n; R++) {
            vl xd;
            for(int k = L; k <= R; k++) {
                xd.eb(a[k]);
            }
            ll sum = accumulate(all(xd), 0LL);
            ll mx = *max_element(all(xd));
            ckmax(ans, sum - mx);
        }
    }
    return ans;
}

ll slv(ll n, vl a) {
    //? <>
    SegTree<ll> st; st.init(n);
    for(int i = 0; i < n; i++) st.upd(i, a[i]);

    vl pref = a; for(int i = 1; i < n; i++)      pref[i] += pref[i - 1];
    vl suff = a; for(int i = n - 2; i >= 0; i--) suff[i] += suff[i + 1];

    dbg(a);
    dbg(pref);
    dbg(suff);

    SegTree<ll> st_pref; st_pref.init(n);
    SegTree<ll> st_suff; st_suff.init(n);
    for(int i = 0; i < n; i++) {
        st_pref.upd(i, pref[i]);
        st_suff.upd(i, suff[i]);
    }

    ll ans = 0;
    for(int C = 0; C < n; C++) {
        RAYA;
        dbg(C, a[C]);
        ll fixedCenter = C;
        ll local_ans = 0;
        {
            ll left = -1; //? always bad
            ll right = C; //? always good
            while(left + 1 < right) {
                ll middle = fdiv(left + right, 2LL);
                if(st.query(middle, fixedCenter) <= a[C]) right = middle;
                else left = middle;
            }
            dbg(right, fixedCenter);
            local_ans += st_suff.query(right, fixedCenter) - suff[fixedCenter];
        }
        {
            ll left = C; //? always good
            ll right = n; //? always bad
            while(left + 1 < right) {
                ll middle = fdiv(left + right, 2LL);
                if(st.query(fixedCenter, middle) <= a[fixedCenter]) left = middle;
                else right = middle;
            }
            dbg(fixedCenter, left);
            local_ans += st_pref.query(fixedCenter, left) - pref[fixedCenter];
        }
        ckmax(ans, local_ans);
    }
    return ans;
}

void solve() {
    //? <>
    ll n; cin >> n;
    vl a(n); each(x, a) cin >> x;
    dbg(n);
    dbg(a);
    ll ans = slv(n, a);
    dbg(ans);
    cout << ans << "\n";
}

//? Generator
mt19937 rng(0);
int rng_int(int L, int R) { assert(L <= R);
	return uniform_int_distribution<int>(L,R)(rng);  }
ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }
//? /Generator

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    while(0) {
        RAYA;
        ll n = rng_ll(1, 20);
        vl a(n); each(x, a) x = rng_ll(-30, 30);
        dbg(n);
        dbg(a);
        ll ans = brute(n, a);
        ll greedy = slv(n, a);
        dbg(ans, greedy);
        chk(ans == greedy);
    }

    int t = 1; //? cin >> t;
    for(int i = 0; i < t; i++) {
        RAYA;
        RAYA;
        solve();
    }
    RAYA;
    RAYA;

    #ifdef LOCAL
        cerr << fixed << setprecision(5);
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
        cerr << "\033[42mtime = " << time_elapsed() << "ms\033[0m\n";
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
    #endif
}
