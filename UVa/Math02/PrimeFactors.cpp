//* sometimes pragmas don't work, if so, just comment it!
//? #pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

//! #undef _GLIBCXX_DEBUG //? for Stress Testing

#include <bits/stdc++.h> //? if you don't want IntelliSense

using namespace std;

#ifdef LOCAL
    #include "helpers/debug.h"
#else
    #define dbg(...)     0
    #define chk(...)     0

    #define RAYA         0
#endif

// building blocks
using ll  = long long;
using db  = long double; // or double, if TL is tight
using str = string;      // yay python!

//? priority_queue for minimum
//? template<class T> using pqg = priority_queue<T, vector<T>, greater<T>>;

//? using ull  = unsigned long long;
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
//! ^ lol this makes everything look weird but I'll try it

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
tcT > int lwb(V<T> &a, const T &b) { return int(lb(all(a), b) - bg(a)); }
tcT > int upb(V<T> &a, const T &b) { return int(ub(all(a), b) - bg(a)); }



// loops
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define rep(a) F0R(_, a)
#define each(a, x) for (auto &a : x)



const int MOD = 1e9 + 7;
const int MX = (int)2e5 + 5;
const ll BIG = 1e18;  //? not too close to LLONG_MAX
const db PI = acos((db)-1);
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};  //? for every grid problem!!
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());



// bitwise ops
// also see https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
constexpr int pct(int x) { return __builtin_popcount(x); }  // # of bits set
constexpr int bits(int x) {  // assert(x >= 0); // make C++11 compatible until
	                         // USACO updates ...
	return x == 0 ? 0 : 31 - __builtin_clz(x);
}  // floor(log2(x))
constexpr int p2(int x) { return 1 << x; }
constexpr int msk2(int x) { return p2(x) - 1; }

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

tcTU > T fstTrue(T lo, T hi, U f) {
	++hi;
	assert(lo <= hi);  // assuming f is increasing
	while (lo < hi) {  // find first index such that f is true
		T mid = lo + (hi - lo) / 2;
		f(mid) ? hi = mid : lo = mid + 1;
	}
	return lo;
}
tcTU > T lstTrue(T lo, T hi, U f) {
	--lo;
	assert(lo <= hi);  // assuming f is decreasing
	while (lo < hi) {  // find first index such that f is true
		T mid = lo + (hi - lo + 1) / 2;
		f(mid) ? lo = mid : hi = mid - 1;
	}
	return lo;
}
tcT > void remDup(vector<T> &v) {  // sort and remove duplicates
	sort(all(v));
	v.erase(unique(all(v)), end(v));
}
tcTU > void safeErase(T &t, const U &u) {
	auto it = t.find(u);
	assert(it != end(t));
	t.erase(it);
}



#define tcTUU tcT, class ...U

const auto beg_time = std::chrono::high_resolution_clock::now();
// https://stackoverflow.com/questions/47980498/accurate-c-c-clock-on-a-multi-core-processor-with-auto-overclock?noredirect=1&lq=1
double time_elapsed() {
	return chrono::duration<double>(std::chrono::high_resolution_clock::now() -
	                                beg_time)
	    .count();
}

inline namespace FileIO {
void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }
void setIO(str s = "") {
	cin.tie(0)->sync_with_stdio(0);  // unsync C / C++ I/O streams
	//? cout << fixed << setprecision(12);
    //? cerr << fixed << setprecision(12);
	cin.exceptions(cin.failbit);
	// throws exception when do smth illegal
	// ex. try to read letter into int
	if (sz(s)) setIn(s + ".in"), setOut(s + ".out");  // for old USACO
}
}  // namespace FileIO



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

const int dddx[8]{1, 0, -1,  0, 1,  1, -1, -1};
const int dddy[8]{0, 1,  0, -1, 1, -1,  1, -1};

//? /Custom Helpers



//* Template
/**
 * Description: Pollard-rho randomized factorization algorithm. Returns prime
   * factors of a number, in arbitrary order (e.g. 2299 -> \{11, 19, 11\}).
 * Time: $O(N^{1/4})$, less for numbers with small factors
 * Source: KACTL
	* https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm
	* https://codeforces.com/contest/1033/submission/44009089 is faster?
 * Verification: https://www.spoj.com/problems/FACT0/
 */

/// using db = long double;
using ul = uint64_t;
ul modMul(ul a, ul b, const ul mod) {
	ll ret = a*b-mod*(ul)((db)a*b/mod);
	return ret+((ret<0)-(ret>=(ll)mod))*mod; }
ul modPow(ul a, ul b, const ul mod) {
	if (b == 0) return 1;
	ul res = modPow(a,b/2,mod); res = modMul(res,res,mod);
	return b&1 ? modMul(res,a,mod) : res;
}



bool prime(ul n) { // not ll!
	if (n < 2 || n % 6 % 4 != 1) return n-2 < 2;
	ul A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
	    s = __builtin_ctzll(n-1), d = n>>s;
	each(a,A) {   // ^ count trailing zeroes
		ul p = modPow(a,d,n), i = s;
		while (p != 1 && p != n-1 && a%n && i--) p = modMul(p,p,n);
		if (p != n-1 && i != s) return 0;
	}
	return 1;
}



ul pollard(ul n) { // return some nontrivial factor of n
	auto f = [n](ul x) { return modMul(x, x, n) + 1; };
	ul x = 0, y = 0, t = 30, prd = 2, i = 1, q;
	while (t++ % 40 || gcd(prd, n) == 1) { /// speedup: don't take gcd every it
		if (x == y) x = ++i, y = f(x);
		if ((q = modMul(prd, max(x,y)-min(x,y), n))) prd = q;
		x = f(x), y = f(f(y));
	}
	return gcd(prd, n);
}
void factor_rec(ul n, map<ul,int>& cnt) {
	if (n == 1) return;
	if (prime(n)) { ++cnt[n]; return; }
	ul u = pollard(n);
	factor_rec(u,cnt), factor_rec(n/u,cnt);
}

V<pair<ul,int>> factor(ul n) {
	map<ul,int> cnt; factor_rec(n,cnt);
	return V<pair<ul,int>>(all(cnt));
}

//* /Template

using E = V<pair<ul,int>>;
void solve() {
    //? <>
    while(true) {
        ll n; cin >> n; if(n == 0) return;
        bool isNeg = (n < 0);
        n = (n < 0)? -n : n;
        E factors = factor(n);
        sor(factors);
        vl ans; if(isNeg) ans.eb(-1);
        for(auto& [f, cnt]: factors) rep(cnt) ans.eb(f);

        if(isNeg) n *= -1LL;
        cout << n << " = ";
        const int M = sz(ans);
        for(int i = 0; i < M; i++) {
            cout << ans[i];
            if(i < M - 1) cout << " x ";
            else cout << "\n";
        }
    }
}


//? Generator
int rng_int(int L, int R) { assert(L <= R);
	return uniform_int_distribution<int>(L,R)(rng);  }
ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }
//? /Generator


signed main() {
    setIO();

    ll t = 1;
    //? cin >> t;

    FOR(i, 1, t + 1) {
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
        cerr << "\033[42m++++++++++++++++++++\033[0m";
    #endif
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
