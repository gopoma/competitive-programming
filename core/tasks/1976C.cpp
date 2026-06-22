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

//? /Custom Helpers



//* Template
/**
 * Author: Lukas Polacek
 * Date: 2009-10-30
 * License: CC0
 * Source: folklore/TopCoder
 * Description: Computes partial sums a[0] + a[1] + ... + a[pos - 1], and updates single elements a[i],
 * taking the difference between the old and new value.
 * Time: Both operations are $O(\log N)$.
 * Status: Stress-tested
 */

tcT> struct BIT {
	int N; V<T> data;
	void init(int _N) { N = _N; data.rsz(N); }
	void add(int p, T x) { for (++p;p<=N;p+=p&-p) data[p-1] += x; }
	T sum(int l, int r) { return sum(r+1)-sum(l); }
	T sum(int r) { T s = 0; for(;r;r-=r&-r)s+=data[r-1]; return s; }
	int lower_bound(T sum) {
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1<<25; pw; pw >>= 1) {
			int npos = pos+pw;
			if (npos <= N && data[npos-1] < sum)
				pos = npos, sum -= data[pos-1];
		}
		return pos;
	}
};

//* /Template

vl brute(ll n, ll m, vl a, vl b) {
    chk(sz(a) == n + m + 1);
    chk(sz(b) == n + m + 1);

    const ll length = n + m + 1;

    vl ans;
    for(int banned = 0; banned < length; banned++) {
        vl group_p, group_t;
        ll sum_p = 0;
        ll sum_t = 0;
        ll nn = n;
        ll mm = m;
        for(int j = 0; j < length; j++) {
            if(j == banned) continue;

            chk(nn >= 0 && mm >= 0);

            chk(a[j] != b[j]);

            if(a[j] > b[j]) {
                if(nn) {
                    sum_p += a[j];
                    nn--;
                    group_p.eb(a[j]);
                } else {
                    sum_t += b[j];
                    mm--;
                    group_t.eb(b[j]);
                }
            } else {
                chk(a[j] < b[j]);

                if(mm) {
                    sum_t += b[j];
                    mm--;
                    group_t.eb(b[j]);
                } else {
                    sum_p += a[j];
                    nn--;
                    group_p.eb(a[j]);
                }
            }
        }

        //? dbg(banned, sum_p, sum_t, group_p, group_t);
        ans.eb(sum_p + sum_t);
    }

    return ans;
}

vl slv(ll n, ll m, vl a, vl b) {
    const ll length = n + m + 1;
    BIT<ll> cnt_a_gt_b; cnt_a_gt_b.init(length);
    BIT<ll> cnt_b_gt_a; cnt_b_gt_a.init(length);

    BIT<ll> pref_a_gt_b; pref_a_gt_b.init(length);
    BIT<ll> pref_b_gt_a; pref_b_gt_a.init(length);

    BIT<ll> pref_a; pref_a.init(length);
    BIT<ll> pref_b; pref_b.init(length);

    for(int i = 0; i < length; i++) {
        pref_a.add(i, a[i]);
        pref_b.add(i, b[i]);
        chk(a[i] != b[i]);

        if(a[i] > b[i]) {
            cnt_a_gt_b.add(i, 1LL);
            pref_a_gt_b.add(i, a[i]);
        } else {
            chk(a[i] < b[i]);

            cnt_b_gt_a.add(i, 1LL);
            pref_b_gt_a.add(i, b[i]);
        }
    }

    dbg(length);
    vl ans(length);
    for(int idx_banned = 0; idx_banned < length; idx_banned++) {
        RAYA;
        //? do
        if(a[idx_banned] > b[idx_banned]) {
            cnt_a_gt_b.add(idx_banned, -1LL);
            pref_a_gt_b.add(idx_banned, -a[idx_banned]);
        } else {
            cnt_b_gt_a.add(idx_banned, -1LL);
            pref_b_gt_a.add(idx_banned, -b[idx_banned]);
        }
        pref_a.add(idx_banned, -a[idx_banned]);
        pref_b.add(idx_banned, -b[idx_banned]);

        int fixedLeft = 0;
        int nn = n;
        int mm = m;
        auto check = [&](int R) -> bool {
            if(R == -1) return false;

            int count_a_gt_b = cnt_a_gt_b.sum(fixedLeft, R);
            int count_b_gt_a = cnt_b_gt_a.sum(fixedLeft, R);

            bool ok = (n - count_a_gt_b <= 0) || (m - count_b_gt_a <= 0);
            if(ok) {
                nn = n - count_a_gt_b;
                mm = m - count_b_gt_a;
                //? dbg(fixedLeft, R, count_a_gt_b, count_b_gt_a, n, m, nn, mm);
            }
            return ok;
        };

        int left = -1; //? always bad
        int right = length - 1; //? always good
        while(left + 1 < right) {
            int middle = (left + right) >> 1;

            if(check(middle)) right = middle;
            else left = middle;
        }

        int L = 0;
        int R = right;

        if(n == 0 || m == 0) {
            R = -1;
            nn = n;
            mm = m;
        }

        //? dbg(idx_banned, L, R, n, m, nn, mm);
        if(R >= 0) {
            ans[idx_banned] = pref_a_gt_b.sum(L, R) + pref_b_gt_a.sum(L, R);
        }
        if(R + 1 < length) {
            //? dbg("pasa");
            //? dbg(nn, mm);
            chk((nn == 0 || mm == 0) && !(nn == 0 && mm == 0));

            int fL = R + 1;
            int fR = length - 1;
            //? dbg(fL, fR);

            if(nn == 0) {
                ll tmp = pref_b.sum(fL, fR);
                ans[idx_banned] += tmp;
                //? dbg(tmp);
            } else {
                chk(mm == 0);
                ll tmp = pref_a.sum(fL, fR);
                ans[idx_banned] += tmp;
                //? dbg(tmp);
            }
        }

        //? undo
        //? do
        if(a[idx_banned] > b[idx_banned]) {
            cnt_a_gt_b.add(idx_banned, +1LL);
            pref_a_gt_b.add(idx_banned, a[idx_banned]);
        } else {
            cnt_b_gt_a.add(idx_banned, +1LL);
            pref_b_gt_a.add(idx_banned, b[idx_banned]);
        }
        pref_a.add(idx_banned, a[idx_banned]);
        pref_b.add(idx_banned, b[idx_banned]);
    }

    return ans;
}

void solve() {
    def(int, n, m);
    vl a(n + m + 1), b(n + m + 1); re(a, b);

    dbg(n, m);
    dbg(a);
    dbg(b);

    vl ans = slv(n, m, a, b);
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

    while(1) {
        RAYA;

        ll n, m;
        while(true) {
            n = rng_int(0, 2);
            m = rng_int(0, 2);

            if(n + m + 1 >= 2) break;
        }

        vl a(n + m + 1), b(n + m + 1);
        for(int i = 0; i < n + m + 1; i++) {
            while(true) {
                ll xx = rng_ll(0, 5);
                ll yy = rng_ll(0, 5);

                if(xx != yy) {
                    a[i] = xx;
                    b[i] = yy;
                    break;
                }
            }
        }

        //? int n = 1;
        //? int m = 0;
        //? vl a{2, 1};
        //? vl b{1, 2};

        dbg(n, m);
        dbg(a);
        dbg(b);

        vl ans = brute(n, m, a, b);
        vl greedy = slv(n, m, a, b);

        dbg(ans);
        dbg(greedy);

        chk(ans == greedy);
    }

    ll t = 1; re(t);

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
