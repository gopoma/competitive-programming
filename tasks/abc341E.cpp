//* sometimes pragmas don't work, if so, just comment it!
//? #pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//? #pragma GCC optimize ("trapv")

//! #undef _GLIBCXX_DEBUG //? for Stress Testing

#include <bits/stdc++.h> //? if you don't want IntelliSense

using namespace std;

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
template <typename... Args> void err(Args... args) {
	Writer<cerr, true, false>{}.print_with_sep(" | ", args...);
}
template <typename... Args> void errn(Args... args) {
	Writer<cerr, true, true>{}.print_with_sep(" | ", args...);
}

void err_prefix(str func, int line, string args) {
	cerr << "\033[0;31m\u001b[1mDEBUG\033[0m"
	     << " | "
	     << "\u001b[34m" << func << "\033[0m"
	     << ":"
	     << "\u001b[34m" << line << "\033[0m"
	     << " - "
	     << "[" << args << "] = ";
}

#ifdef LOCAL
#define dbg(args...) err_prefix(__FUNCTION__, __LINE__, #args), err(args)
#define dbgn(args...) err_prefix(__FUNCTION__, __LINE__, #args), errn(args)

#define chk(...) if (!(__VA_ARGS__)) cerr << "\033[41m" << "Line(" << __LINE__ << ") -> function(" \
	 << __FUNCTION__  << ") -> CHK FAILED: (" << #__VA_ARGS__ << ")" << "\033[0m" << "\n", exit(0);

#define MACRO(code) do {code} while (false)
#define RAYA MACRO(cerr << "\033[101m" << "================================" << "\033[0m" << endl;)
#else
#define dbg(...)
#define dbgn(args...)

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

//? /Custom Helpers



//* Template
/**
 * Description: 1D range increment and sum query.
 * Source: USACO Counting Haybales
 	* https://codeforces.com/blog/entry/82400
 * Verification: USACO Counting Haybales
 */

struct LazySeg {
	struct F { // lazy update
		ll inc = 0;
        ll mul = 1;
		F() {}
		F(int x, int y) {
            inc = x; mul = y;
        }
		F& operator*=(const F& a) {
            inc += a.inc;
            mul *= a.mul;
            return *this;
        }
	}; V<F> lazy;
	struct T { // data you need to store for each interval
		ll sz = 1, mn = BIG, sum = 0;

        bool ok = true;
        ll front = ll(1e12);
        ll back  = ll(1e12);


		T() {}
		T(int x) {
            mn = sum = x;

            front = x;
            back = x;
        }
		friend T operator+(const T& a, const T& b) {
            //? YES
			T res; res.sz = a.sz+b.sz;

            //? NO
            res.mn = min(a.mn,b.mn), res.sum = a.sum+b.sum;

            bool global_ok = true;
            if(!(a.ok && b.ok)) {
                res.ok = false;
                global_ok = false;
            } else {
                if(a.back != b.front) res.ok = true;
                else res.ok = false;
            }

            if(global_ok && (a.back < ll(-1e9) || a.back > ll(1e9))) {
                res.ok = true;
            }
            if(global_ok && (b.front < ll(-1e9) || b.front > ll(1e9))) {
                res.ok = true;
            }

            res.front = a.front;
            res.back =  b.back;

			return res;
		}
		T& operator*=(const F& a) {
			mn += a.inc;
            sum *= a.mul;
            sum += (ll)sz*a.inc;


            front *= a.mul;
            front += (ll)sz*a.inc;

            back *= a.mul;
            back += (ll)sz*a.inc;

            return *this;
        }
	}; V<T> seg;
	int SZ = 1;
	void init(const V<T>& _seg) {
		while (SZ < sz(_seg)) SZ *= 2;
		seg.rsz(2*SZ); lazy.rsz(2*SZ);
		F0R(i,SZ) seg[SZ+i] = _seg[i];
		ROF(i,1,SZ) pull(i);
	}
	void push(int ind) { /// modify values for current node
		seg[ind] *= lazy[ind];
		if (ind < SZ) F0R(i,2) lazy[2*ind+i] *= lazy[ind];
		lazy[ind] = F();
	} // recalc values for current node
	void pull(int ind) { seg[ind] = seg[2*ind]+seg[2*ind+1]; }
	void upd(int lo, int hi, F inc, int ind, int L, int R) {
		push(ind); if (hi < L || R < lo) return;
		if (lo <= L && R <= hi) {
			lazy[ind] = inc; push(ind); return; }
		int M = (L+R)/2; upd(lo,hi,inc,2*ind,L,M);
		upd(lo,hi,inc,2*ind+1,M+1,R); pull(ind);
	}
	void upd(int lo, int hi, int inc, int mul) { upd(lo,hi,F(inc, mul),1,0,SZ-1); }
	T query(int lo, int hi, int ind, int L, int R) {
		push(ind); if (lo > R || L > hi) return T();
		if (lo <= L && R <= hi) return seg[ind];
		int M = (L+R)/2;
		return query(lo,hi,2*ind,L,M)+query(lo,hi,2*ind+1,M+1,R);
	}
	T query(int lo, int hi) { return query(lo,hi,1,0,SZ-1); }
};
//* /Template

void solve() {
    def(int, N, Q);
    def(str, S);

    vector<tuple<int, int, int>> queries(Q); re(queries);
    each(x, queries) dbg(x);

    RAYA;

    vector<LazySeg::T> arr;


    for(int i = 0; i < N; i++) {
        arr.eb(LazySeg::T(int(S[i] - '0')));
    }

    int go = 1;
    while(go < N) go *= 2;
    while(N < go) {
        arr.eb(LazySeg::T(0));
        go--;
    }

    LazySeg tree; tree.init(arr);
    #define xd for(int g = 0; g < N; g++) { dbg(tree.query(g, g).sum); } RAYA;

    xd

    for(int i = 0; i < Q; i++) {
        int type, left, right;
        tie(type, left, right) = queries[i];
        left--; right--;
        dbg(type, left, right);

        if(type == 1) {
            tree.upd(left, right, 1, -1);
        } else if(type == 2) {
            bool ans = tree.query(left, right).ok;

            if(ans) ps("Yes");
            else ps("No");
        } else assert(false);

        xd
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

    ll t = 1; //? re(t);

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