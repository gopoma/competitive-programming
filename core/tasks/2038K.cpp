//* sometimes pragmas don't work, if so, just comment it!
#pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

#undef _GLIBCXX_DEBUG //? for Stress Testing

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

using vvi = V<vi>;
using vvl = V<vl>;
using vvb = V<vb>;



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



ll cdiv(ll a, ll b) {
	return a / b + ((a ^ b) > 0 && a % b);
}  // divide a by b rounded up
ll fdiv(ll a, ll b) {
	return a / b - ((a ^ b) < 0 && a % b);
}  // divide a by b rounded down

tcT > bool ckmin(T &a, const T &b) {
	return b < a ? a = b, 1 : 0;
}  // set a = min(a,b)
tcT > bool ckmax(T &a, const T &b) {
	return a < b ? a = b, 1 : 0;
}  // set a = max(a,b)

tcT > void remDup(vector<T> &v) {  // sort and remove duplicates
	sort(all(v));
	v.erase(unique(all(v)), end(v));
}
tcTU > void safeErase(T &t, const U &u) {
	auto it = t.find(u);
	assert(it != end(t));
	t.erase(it);
}



//? Custom Helpers
template <typename T>
inline T gcd(T a, T b) { while (b != 0) swap(b, a %= b); return a; }

long long binpow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

//? __builtin_popcountll
ll GetBit(ll mask, ll bit) { return (mask >> bit) & 1LL; }
void TurnOn(ll& mask, ll bit) { mask = mask | (1LL << bit); }
void TurnOff(ll& mask, ll bit) { mask = mask & (~(1LL << bit)); }

const int dddx[8]{1, 0, -1,  0, 1,  1, -1, -1};
const int dddy[8]{0, 1,  0, -1, 1, -1,  1, -1};

using vvi = V<vi>;
using vvl = V<vl>;
using vvb = V<vb>;

const int MOD = 1e9 + 7;
const int MX = (int)2e5 + 5;
const ll BIG = 1e18;  //? not too close to LLONG_MAX
const db PI = acos((db)-1);
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};  //? for every grid problem!!
mt19937 rng(0);

int rng_int(int L, int R) { assert(L <= R);
	return uniform_int_distribution<int>(L,R)(rng);  }
ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }
//? /Custom Helpers

//? Template
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
    T ID{}; T cmb(T a, T b) { return a+b; }
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
// /here goes the template!

struct node {
    ll val; // min
    ll idx; // max

	node(): val(+BIG), idx(-BIG) {}

	node(ll _val, ll _idx) : val(_val), idx(_idx) {}

	node operator + (const node &rhs) const {
        if(val < rhs.val) return node(val, idx);
        else if(val > rhs.val) return node(rhs.val, rhs.idx);
        else return node(val, max(idx, rhs.idx));
	}
};
//? /Template

ll brute(ll n, ll a, ll b) {
    vvl c(n + 1, vl(n + 1));
    for(ll i = 1; i <= n; i++) {
        for(ll j = 1; j <= n; j++) {
            c[i][j] = gcd(i, a) + gcd(j, b);
        }
    }
    auto check = [&](int i, int j) -> bool {
        return (0 < i && i <= n) && (0 < j && j <= n);
    };
    vvl dp(n + 1, vl(n + 1, BIG));
    dp[1][1] = c[1][1];
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(check(i - 1, j)) ckmin(dp[i][j], dp[i - 1][j] + c[i][j]);
            if(check(i, j - 1)) ckmin(dp[i][j], dp[i][j - 1] + c[i][j]);
        }
    }
    for(int i = 1; i <= n; i++) {
        //? dbg(i, dp[i][i]);
    }
    //? RAYA;
    //? dbg("dp");
    //? each(x, dp) dbg(x);
    //? RAYA;
    //? dbg("c");
    //? each(x, c) dbg(x);
    //? RAYA;
    return dp[n][n];
}

ll slv(ll n, ll a, ll b) {
    SegTree<node> st_row; st_row.init(n + 5);
    SegTree<node> st_col; st_col.init(n + 5);
    for(ll i = 1; i <= n; i++) st_row.upd(i, node(gcd(i, a), i));
    for(ll i = 1; i <= n; i++) st_col.upd(i, node(gcd(i, b), i));

    ll cur_r = 1;
    vi rows{cur_r};
    while(cur_r != n) {
        ll hasta_r = st_row.query(cur_r + 1, n).idx;
        rows.eb(hasta_r);
        cur_r = hasta_r;
    }
    ll cur_c = 1;
    vi cols{cur_c};
    while(cur_c != n) {
        ll hasta_c = st_col.query(cur_c + 1, n).idx;
        cols.eb(hasta_c);
        cur_c = hasta_c;
    }
    //? dbg(rows, cols);

    vl sum_row(n + 5);
    for(ll i = 1; i < sz(sum_row); i++) {
        sum_row[i] = gcd(i, a);
        sum_row[i] += sum_row[i - 1];
    }
    vl sum_col(n + 5);
    for(ll i = 1; i < sz(sum_col); i++) {
        sum_col[i] = gcd(i, b);
        sum_col[i] += sum_col[i - 1];
    }
    auto query = [&](vl& pref, int L, int R) -> ll {
        ll sum = pref[R];
        if(0 <= L - 1) sum -= pref[L - 1];
        return sum;
    };

    const int N = sz(rows);
    const int M = sz(cols);
    vvl dp(N + 1, vl(M + 1, BIG));
    dp[0][0] = 2LL;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if(j + 1 < M) { // [i][j + 1]
                ckmin(dp[i][j + 1], 
                    dp[i][j] + 
                    query(sum_col, cols[j] + 1LL, cols[j + 1]) + 
                    (cols[j + 1] - cols[j]) * gcd(rows[i], a)
                );
            }   
            if(i + 1 < N) { // [i + 1][j]
                ckmin(dp[i + 1][j], 
                    dp[i][j] + 
                    query(sum_row, rows[i] + 1LL, rows[i + 1]) +
                    (rows[i + 1] - rows[i]) * gcd(cols[j], b)
                );
            }         
        }
    }

    return dp[N - 1][M - 1];
}

void solve() {
    //? <>
    ll n, a, b; cin >> n >> a >> b;
    dbg(n, a, b);
    ll ans = slv(n, a, b);
    dbg(ans);
    cout << ans << "\n";
}

void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    //? Stress Testing
    while(0) {
        RAYA;
        ll n = rng_ll(2, 100);
        ll a = rng_ll(1, 100);
        ll b = rng_ll(1, 100);
        dbg(n, a, b);
        ll ans = brute(n, a, b);
        ll greedy = slv(n, a, b);
        dbg(ans, greedy);
        chk(ans == greedy);
    }

    int t = 1; //! cin >> t;
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
