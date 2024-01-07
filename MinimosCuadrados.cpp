//? template: https://github.com/bqi343/cp-notebook/blob/master/Implementations/content/contest/TemplateLong.cpp
// sometimes pragmas don't work, if so, just comment it!
//? #pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx2")
//! #pragma GCC optimize ("trapv")

#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
    #include "helpers/debug.h"
#else
    #define dbg(...)     0
    #define chk(...)     0

    #define RAYA         0
#endif



// building blocks
using ll = long long;
using ull = unsigned long long;
using db = long double; // or double, if TL is tight
using str = string;     // yay python!
// using i64 = long long;    //? for Number Theory related
// using u64 = uint64_t;     //? for Number Theory related
// using i128 = __int128;    //? for Number Theory related
// using u128 = __uint128_t; //? for Number Theory related
template<class T> using pqg = priority_queue<T, vector<T>, greater<T>>; //? minima



// pairs
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<db, db>;

#define mp make_pair
#define f  first
#define s  second



#define tcT template<class T
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



const int MOD = 998244353;   //? 1e9+7;
const int MX = (int)2e5 + 5;
const ll BIG = 1e18;         //? not too close to LLONG_MAX
const db PI = acos((db)-1);
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};  // for every grid problem!!
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
}  //? divide a by b rounded up
ll fdiv(ll a, ll b) {
	return a / b - ((a ^ b) < 0 && a % b);
}  //? divide a by b rounded down

tcT > bool ckmin(T &a, const T &b) {
	return b < a ? a = b, 1 : 0;
}  //? set a = min(a,b)
tcT > bool ckmax(T &a, const T &b) {
	return a < b ? a = b, 1 : 0;
}  //? set a = max(a,b)

tcTU > T fstTrue(T lo, T hi, U f) {
	++hi;
	assert(lo <= hi);  //? assuming f is increasing
	while (lo < hi) {  //? find first index such that f is true
		T mid = lo + (hi - lo) / 2;
		f(mid) ? hi = mid : lo = mid + 1;
	}
	return lo;
}
tcTU > T lstTrue(T lo, T hi, U f) {
	--lo;
	assert(lo <= hi);  //? assuming f is decreasing
	while (lo < hi) {  //? find first index such that f is true
		T mid = lo + (hi - lo + 1) / 2;
		f(mid) ? lo = mid : hi = mid - 1;
	}
	return lo;
}

tcT > void remDup(vector<T> &v) {  //? sort and remove duplicates
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



inline namespace FileIO {
    void setIn(str s) { freopen(s.c_str(), "r", stdin); }
    void setOut(str s) { freopen(s.c_str(), "w", stdout); }
    void setIO(str s = "") {
	    cin.tie(0)->sync_with_stdio(0);  //! unsync C / C++ I/O streams
	    cout << fixed << setprecision(6);
        cerr << fixed << setprecision(6);
	    cin.exceptions(cin.failbit);
	    //? throws exception when do smth illegal
	    //? ex. try to read letter into int
	    if (sz(s)) setIn(s + ".in"), setOut(s + ".out");  // for old USACO
}
}  // namespace FileIO



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

//* here goes the template!
//* /here goes the template!


//* Capítulo_4 Diapositiva 74
//* const vd x = {0.3, 2.7, 4.5, 5.9, 7.8,};
//* const vd y = {1.8, 1.9, 3.1, 3.9, 3.3,};
//* const int grado = 1;


//* Chapra Página 360
//* const vd x = {  1,   2, 3, 4,   5, 6,   7};
//* const vd y = {0.5, 2.5, 2, 4, 3.5, 6, 5.5};
//* const int grado = 1;
//* y = 0.0714 + 0.8393x

//* const int grado = 2;
//* const vd x = {  0,   1,    2,    3,    4,    5};
//* const vd y = {2.1, 7.7, 13.6, 27.2, 40.9, 61.1};
//* y = 2.4786 + 2.3593x + 1.8607x^2

// const int grado = 2;
// const vd x = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0};
// const vd y = {1.7, 0.3, 5.6, 7.8, 10.0, 11.0, 12.0, 14.0};
//* y = 0.3167 + 2.6321*x - 0.0988*x*x

//* const int grado = 3;
//* const vd x = {};
//* const vd y = {};

//* Chapra Página 368
//* const int grado = 1;
//* vd x = {  1,   2,   3,   4,   5};
//* vd y = {0.5, 1.7, 3.4, 5.7, 8.4};
//! y = a * (x ^ b)
//! ln(y) = ln(a * (x ^ b))
//! ln(y) = ln(a) + ln(x ^ b)
//! ln(y) = ln(a) + b * ln(x)
//! make Y = ln(y) | A = a | X = ln(x)
//* Y = A + b * X
//* Y = -0.6913 + 1.7517*x
//! ln(a) = A -> ln(a) = -0.6913 -> a = 0.500924
//! b = 1.7517
//? y = 0.500924 * (x ^ 1.7517)

const int grado = 1;
vd x;
vd y;

void solve() {
    //? dbg(log(2.0)); //! Natural Logarithm
    //! transform
    //! for(auto& e: x) e = log(e);
    //! for(auto& e: y) e = log(e);
    //!

    chk(sz(x) == sz(y));
    const int n = sz(x);
    const int need = 2 * grado + 1;

    vd sum_x(need, 0.0); //? sum_x[i] = sum [x ** i]
    for(int i = 1; i < need; i++) {
        sum_x[i] = accumulate(all(x), 0.0,
            [&](const db& acc, const db& current) {
                return acc + pow(current, db(i));
            }
        );
    }

    vd sum_y(grado + 2, 0.0); //? sum_y[i] = sum [y * (x ** (i - 1))]
    for(int i = 1; i < grado + 2; i++) {
        for(int j = 0; j < n; j++) {
            sum_y[i] += y[j] * pow(x[j], db(i - 1));
        }
    }

    dbg(x);
    dbg(y);
    dbg(grado);
    RAYA;
    dbg(n);

    const str _$1 = "sum_x[i] = sum [x ** i]";
    dbg(_$1, sum_x);

    const str _$2 = "sum_y[i] = sum [y * (x ** (i - 1))]";
    dbg(_$2, sum_y);
}



clock_t startTime;
double getCurrentTime() { return (double)(clock() - startTime) / CLOCKS_PER_SEC; }
signed main() {
    startTime = clock();

    // read read read
    setIO();

    ll t = 1LL;
    //? cin >> t;

    for(ll i = 0; i < t; i++) {
        RAYA;
        RAYA;
        solve();
    }
    RAYA;
    RAYA;

    #ifdef LOCAL
        cerr << fixed << setprecision(5);
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
        cerr << "\033[42mtime = " << getCurrentTime() << "ms\033[0m\n";
        cerr << "\033[42m++++++++++++++++++++\033[0m";
    #endif

    // should actually read the stuff at the bottom
}

/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	! do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
	! DON'T GET STUCK ON ONE APPROACH
*/
