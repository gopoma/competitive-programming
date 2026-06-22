//* sometimes pragmas don't work, if so, just comment it!
//? #pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

//! #undef _GLIBCXX_DEBUG //? for Stress Testing

#include <bits/stdc++.h> //? if you don't want IntelliSense

using namespace std;

// building blocks
using ll  = long long;
using db  = long double; // or double, if TL is tight
using str = string;      // yay python!

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
mt19937 rng(0);


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

inline namespace IO {
#define SFINAE(x, ...)                                                         \
	template <class, class = void> struct x : std::false_type {};              \
	template <class T> struct x<T, std::void_t<__VA_ARGS__>> : std::true_type {}

SFINAE(DefaultI, decltype(std::cin >> std::declval<T &>()));
SFINAE(DefaultO, decltype(std::cout << std::declval<T &>()));
SFINAE(IsTuple, typename std::tuple_size<T>::type);
SFINAE(Iterable, decltype(std::begin(std::declval<T>())));

template <auto &is> struct Reader {
	template <class T> void Impl(T &t) {
		if constexpr (DefaultI<T>::value) is >> t;
		else if constexpr (Iterable<T>::value) {
			for (auto &x : t) Impl(x);
		} else if constexpr (IsTuple<T>::value) {
			std::apply([this](auto &...args) { (Impl(args), ...); }, t);
		} else static_assert(IsTuple<T>::value, "No matching type for read");
	}
	template <class... Ts> void read(Ts &...ts) { ((Impl(ts)), ...); }
};

template <class... Ts> void re(Ts &...ts) { Reader<cin>{}.read(ts...); }
#define def(t, args...)                                                        \
	t args;                                                                    \
	re(args);

template <auto &os, bool debug, bool print_nd> struct Writer {
	string comma() const { return debug ? "," : ""; }
	template <class T> constexpr char Space(const T &) const {
		return print_nd && (Iterable<T>::value or IsTuple<T>::value) ? '\n'
		                                                             : ' ';
	}
	template <class T> void Impl(T const &t) const {
		if constexpr (DefaultO<T>::value) os << t;
		else if constexpr (Iterable<T>::value) {
			if (debug) os << '{';
			int i = 0;
			for (auto &&x : t)
				((i++) ? (os << comma() << Space(x), Impl(x)) : Impl(x));
			if (debug) os << '}';
		} else if constexpr (IsTuple<T>::value) {
			if (debug) os << '(';
			std::apply(
			    [this](auto const &...args) {
				    int i = 0;
				    (((i++) ? (os << comma() << " ", Impl(args)) : Impl(args)),
				     ...);
			    },
			    t);
			if (debug) os << ')';
		} else static_assert(IsTuple<T>::value, "No matching type for print");
	}
	template <class T> void ImplWrapper(T const &t) const {
		if (debug) os << "\033[0;31m";
		Impl(t);
		if (debug) os << "\033[0m";
	}
	template <class... Ts> void print(Ts const &...ts) const {
		((Impl(ts)), ...);
	}
	template <class F, class... Ts>
	void print_with_sep(const std::string &sep, F const &f,
	                    Ts const &...ts) const {
		ImplWrapper(f), ((os << sep, ImplWrapper(ts)), ...), os << '\n';
	}
	void print_with_sep(const std::string &) const { os << '\n'; }
};

template <class... Ts> void pr(Ts const &...ts) {
	Writer<cout, false, true>{}.print(ts...);
}
template <class... Ts> void ps(Ts const &...ts) {
	Writer<cout, false, true>{}.print_with_sep(" ", ts...);
}
}  // namespace IO

inline namespace Debug {

#ifdef LOCAL
#include "helpers/debug.h"

#define chk(...) if (!(__VA_ARGS__)) cerr << "\033[41m" << "Line(" << __LINE__ << ") -> function(" \
	 << __FUNCTION__  << ") -> CHK FAILED: (" << #__VA_ARGS__ << ")" << "\033[0m" << "\n", exit(0);

#define MACRO(code) do {code} while (false)
#define RAYA MACRO(cerr << "\033[101m" << "================================" << "\033[0m" << endl;)
#else
#define dbg(...)

#define chk(...)
#define RAYA
#endif

const auto beg_time = std::chrono::high_resolution_clock::now();
// https://stackoverflow.com/questions/47980498/accurate-c-c-clock-on-a-multi-core-processor-with-auto-overclock?noredirect=1&lq=1
double time_elapsed() {
	return chrono::duration<double>(std::chrono::high_resolution_clock::now() -
	                                beg_time)
	    .count();
}
}  // namespace Debug



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

using vvi = V<vi>;
using vvl = V<vl>;
using vvb = V<vb>;
//? /Custom Helpers



//* Template
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
    T ID{}; T cmb(T a, T b) { return max(a, b); }
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
//* /Template

ll brute(ll H, ll W, ll N, vpl coins) {
    set<pl> good; each(x, coins) good.emplace(x);
    auto check = [&](ll xx, ll yy)  -> bool {
        return (1 <= xx && xx <= H) && (1 <= yy && yy <= W);
    };
    map<ll, map<ll, bool>> vis;
    map<ll, map<ll, ll>> memo;
    function<ll(ll, ll)> dp = [&](ll xx, ll yy) -> ll {
        if(xx == H && yy == W) return 0LL;
        if(vis[xx][yy]) return memo[xx][yy];
        vis[xx][yy] = true;
        ll ans = -BIG;
        if(check(xx + 1, yy)) ckmax(ans, dp(xx + 1, yy) + ll(good.count(mp(xx + 1, yy))));
        if(check(xx, yy + 1)) ckmax(ans, dp(xx, yy + 1) + ll(good.count(mp(xx, yy + 1))));
        return memo[xx][yy] = ans;
    };
    return dp(1, 1);
}

void solve(ll H, ll W, ll N, vpl coins) {
    //? <>
    map<int, vector<int>> where;
    for(auto& [xx, yy]: coins) {
        where[xx].eb(yy);
    }
    for(auto& [k, v]: where) {
        sor(v);
    }
    //? dbg(where);



    vpi positions;
    vi arr;
    for(auto& [xx, cols]: where) {
        each(yy, cols) {
            positions.eb(xx, yy);
            arr.eb(yy);
        }
    }
    //? dbg(positions);
    //? dbg(arr);



    const int MAXN = W + 20;
    SegTree<int> st; st.init(MAXN);
    st.ID = 0;
    vl dp(N);
    for(int i = 0; i < N; i++) {
        auto val = st.query(0, arr[i]);
        st.upd(arr[i], val + 1);
        dp[i] = val + 1;
    }
    //? auto ddd = [&]() -> void {
    //?     vi xd;
    //?     for(int i = 0; i < MAXN; i++) xd.eb(st.query(i, i));
    //?     dbg(xd);
    //? };
    //? ddd();
    //? dbg(dp);
    ll tar_idx = -1;
    ll mx = -BIG;
    for(ll i = 0; i < N; i++) if(mx < dp[i]) {
        mx = dp[i];
        tar_idx = i;
    }
    chk(tar_idx != -1);

    vl tar_positions; tar_positions.eb(tar_idx);
    ll current_value = arr[tar_idx];
    ll current_ans = dp[tar_idx];
    ll mx_coins = dp[tar_idx];
    tar_idx--;
    while(tar_idx >= 0) {
        if(arr[tar_idx] <= current_value && dp[tar_idx] + 1 == current_ans) {
            current_ans--;
            current_value = arr[tar_idx];
            tar_positions.eb(tar_idx);
        }
        tar_idx--;
    }
    vpi locations; locations.eb(1, 1);
    reverse(all(tar_positions));
    for(auto& idx: tar_positions) locations.eb(positions[idx]);
    locations.eb(H, W);
    //? dbg(arr);
    //? dbg(dp);
    //? dbg(positions);
    //? dbg(tar_positions);
    //? dbg(locations);

    str ans;
    const int M = sz(locations);
    for(int i = 0; i < M - 1; i++) {
        auto [xx, yy] = locations[i];
        auto [xx2, yy2] = locations[i + 1];
        ll delta_x = xx2 - xx; assert(delta_x >= 0);
        ll delta_y = yy2 - yy; assert(delta_y >= 0);
        rep(delta_x) ans.pb('D');
        rep(delta_y) ans.pb('R');
    }
//?    {
//?        //? dbg(arr);
//?        //? dbg(H, W, N);
//?        //? dbg(coins);
//?        dbg("Brute");
//?        ll brute_ans = brute(H, W, N, coins);
//?        dbg("Greedy");
//?        dbg(brute_ans);
//?        dbg(mx_coins);
//?        chk(brute_ans == mx_coins);
//?    }
//?    {
//?        chk(sz(ans) == H + W - 2LL);
//?        set<pl> good; each(x, coins) good.emplace(x);
//?        auto check = [&](ll xx, ll yy)  -> bool {
//?            return (1 <= xx && xx <= H) && (1 <= yy && yy <= W);
//?        };
//?        ll cx = 1, cy = 1;
//?        chk(check(cx, cy));
//?        ll xd = 0;
//?        each(c, ans) {
//?            xd += good.count(mp(cx, cy));
//?            if(c == 'R') cy++;
//?            else cx++;
//?            chk(check(cx, cy));
//?        }
//?        dbg(H, W, N);
//?        dbg(coins);
//?        dbg(ans);
//?        dbg(xd);
//?        dbg(mx_coins);
//?        chk(xd == mx_coins);
//?    }

    dbg(mx_coins);
    ps(mx_coins);
    dbg(ans);
    ps(ans);
}


//? Generator
int rng_int(int L, int R) { assert(L <= R);
	return uniform_int_distribution<int>(L,R)(rng);  }
ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }
//? /Generator


signed main() {
    setIO();

    while(0) {
        RAYA;
        ll H = rng_ll(2, ll(5));
        ll W = rng_ll(2, ll(5));
        ll N = rng_ll(2, max(2LL, H * W - 2LL));
        vpl coins(N); each(x, coins) {
            x.f = rng_ll(1, H);
            x.s = rng_ll(1, W);
        }
        {
            vpl xd;
            for(auto& [xx, yy]: coins) {
                if(mp(xx, yy) != mp(1LL, 1LL) && mp(xx, yy) != mp(H, W)) {
                    xd.eb(xx, yy);
                }
            }
            swap(coins, xd);
            N = sz(coins);
        }
        remDup(coins);
        N = sz(coins);
        if(N == 0) continue;
        solve(H, W, N, coins);
    }

    ll t = 1; //? re(t);

    FOR(i, 1, t + 1) {
        RAYA;
        RAYA;
        def(ll, H, W, N);
        vpl coins(N); re(coins);
        //? dbg(H, W, N);
        //? dbg(coins);
        solve(H, W, N, coins);
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
