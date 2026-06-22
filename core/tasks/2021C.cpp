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
//* /Template

bool gocheck(ll n, ll m, vl a, vl b) {
    map<ll, ll> sortedPosition;
	for(int i = 0; i < n; i++) 
		sortedPosition[a[i]] = i;
 
	map<ll, ll> positionInQueue;
	for(int i = 0; i < m; i++) 
		if(!positionInQueue.count(b[i])) 
			positionInQueue[b[i]] = i;
 
	vpl xd; 
	for(auto& [val, idx]: positionInQueue) 
		xd.eb(idx, val);
	
	sor(xd);
 
	bool ok = (sortedPosition[xd.ft.s] == 0);
 
	for(int i = 0; i < sz(xd) - 1; i++) 
		ok &= (sortedPosition[xd[i].s] + 1 == sortedPosition[xd[i + 1].s]);
    return ok;
}

vb brute(ll n, ll m, ll q, vl a, vl b, vpl queries) {
    each(x, a) x--;
    each(x, b) x--;
    each(x, queries) { x.f--; x.s--; }
    
    vb response{gocheck(n, m, a, b)};
    for(auto& [idx, val]: queries) {
        b[idx] = val;
        response.eb(gocheck(n, m, a, b));
    }
    return response;
}

vb slv(ll n, ll m, ll q, vl a, vl b, vpl queries) {
    each(x, a) x--;
    each(x, b) x--;
    each(x, queries) { x.f--; x.s--; }

    vl sortedPositions(n);
    for(int i = 0; i < n; i++) sortedPositions[a[i]] = i;
    //? for(int u = 0; u < n; u++) dbg(u, sortedPositions[u]);
    //? RAYA;

    set<pl> sortedVector; map<ll, ll> sortedVectorBackwards;
    map<ll, set<ll>> locationsInB;
    map<pl, bool> isGood;
    ll goods = 0, bads = 0;

    auto isFirstInSortedVector = [&](ll idx, ll val) {
        return (mp(idx, val) == (*sortedVector.begin()));
    };

    auto check = [&](ll idx, ll val) -> bool {
        if(isFirstInSortedVector(idx, val)) {
            return (sortedPositions[val] == 0);
        } else {
            auto it_prv = sortedVector.find(mp(idx, val));
            it_prv--;
            auto [idx_prv, val_prv] = *it_prv;
            return (sortedPositions[val_prv] + 1 == sortedPositions[val]);
        }
    };

    auto manageDeleteInGood = [&](ll idx, ll val) -> void {
        if(isGood.count(mp(idx, val))) {
            if(isGood[mp(idx, val)]) goods--;
            else bads--;
        }
    };

    auto checkAndUpdate = [&](ll idx, ll val) {
        manageDeleteInGood(idx, val);

        if(check(idx, val)) {
            isGood[mp(idx, val)] = true;
            goods++;
        } else {
            isGood[mp(idx, val)] = false;
            bads++;
        }
    };

    auto add = [&](ll idx, ll val) -> void {
        if(locationsInB[val].empty()) {
            dbg("locationsInB[val].empty()");
            //? add
            sortedVector.emplace(idx, val);
            locationsInB[val].emplace(idx);

            //? check current
            checkAndUpdate(idx, val);
            
            //? check nxt
            {
                auto it_nxt = sortedVector.find(mp(idx, val));
                it_nxt++;
                if(it_nxt != sortedVector.end()) {
                    auto [idx_nxt, val_nxt] = *it_nxt;
                    checkAndUpdate(idx_nxt, val_nxt);
                }
            }
        } else if(idx < (*locationsInB[val].begin())) {
            dbg("idx < (*locationsInB[val].begin())");
            //? dbg(idx, val, locationsInB, sortedVector, goods, bads);
            //? there's better option
            //? delete
            {
                manageDeleteInGood(*locationsInB[val].begin(), val);

                auto it_nxt = sortedVector.find(mp(*locationsInB[val].begin(), val));
                it_nxt++;
                if(it_nxt != sortedVector.end()) {
                    dbg("there's sig");
                    safeErase(sortedVector, mp(*locationsInB[val].begin(), val));
                    auto [idx_nxt, val_nxt] = *it_nxt;
                    checkAndUpdate(idx_nxt, val_nxt);
                } else {
                    dbg("no sig");
                    safeErase(sortedVector, mp(*locationsInB[val].begin(), val));
                }
                safeErase(isGood, mp(*locationsInB[val].begin(), val));
                //? safeErase(locationsInB[val], *locationsInB[val].begin());
            }

            //? add
            locationsInB[val].emplace(idx);
            sortedVector.emplace(idx, val);
            //? check current
            //? dbg(goods, bads, sortedVector);
            checkAndUpdate(idx, val);
            //? dbg(goods, bads,sortedVector);
            
            //? check nxt
            {
                auto it_nxt = sortedVector.find(mp(idx, val));
                it_nxt++;
                if(it_nxt != sortedVector.end()) {
                    auto [idx_nxt, val_nxt] = *it_nxt;
                    checkAndUpdate(idx_nxt, val_nxt);
                }
            }
        } else {
            dbg("just add");
            locationsInB[val].emplace(idx);
        }
    };

    auto del = [&](ll idx, ll val) {
        if(idx == (*locationsInB[val].begin())) {
            dbg("Deleting First");
            { //? delete current
                auto it_nxt = sortedVector.find(mp(idx, val));
                it_nxt++;

                manageDeleteInGood(*locationsInB[val].begin(), val);

                if(it_nxt != sortedVector.end()) {
                    safeErase(sortedVector, mp(idx, val));
                    auto [idx_nxt, val_nxt] = *it_nxt;
                    checkAndUpdate(idx_nxt, val_nxt);
                } else {
                    safeErase(sortedVector, mp(idx, val));
                }
                safeErase(locationsInB[val], idx);
                safeErase(isGood, mp(idx, val));
            }


            //? add nxt
            if(!locationsInB[val].empty()) {
                //? add
                sortedVector.emplace(*locationsInB[val].begin(), val);
                locationsInB[val].emplace(*locationsInB[val].begin());

                //? check current
                checkAndUpdate(*locationsInB[val].begin(), val);

                //? check nxt
                {
                    auto it_nxt = sortedVector.find(mp(*locationsInB[val].begin(), val));
                    it_nxt++;
                    if(it_nxt != sortedVector.end()) {
                        auto [idx_nxt, val_nxt] = *it_nxt;
                        checkAndUpdate(idx_nxt, val_nxt);
                    }
                }
            }
        } else {
            dbg("doesn't mind", locationsInB, val, idx);
            safeErase(locationsInB[val], idx);
        }
    };

    for(int i = 0; i < m; i++) {
        //? RAYA;
        add(i, b[i]);
        //? dbg(i, b[i], sortedVector, goods, bads);
    }
    //? RAYA;
    dbg("Initial Config");
    dbg(goods, bads);
    dbg(sortedVector);
    dbg(locationsInB);
    dbg(a);
    dbg(b);
    RAYA;

    vb response;
    {
        bool ok = (goods == sz(sortedVector));
        response.eb(ok);
        //? cout << (ok?"YA":"TIDAK") << "\n";
    }

    for(auto& [idx, new_b_val]: queries) {
        RAYA;
        dbg("Before", idx, new_b_val, b, sortedVector, goods, bads, locationsInB);

        //? del
        del(idx, b[idx]);
        dbg("After Delete", sortedVector, goods, bads, locationsInB);

        //? add
        add(idx, new_b_val);
        b[idx] = new_b_val;

        dbg("After Add", b, sortedVector, goods, bads, locationsInB);
        bool ok = (goods == sz(sortedVector));
        response.eb(ok);
        //? cout << (ok?"YA":"TIDAK") << "\n";
    }
    return response;
}

void solve() {
    //? <>
    def(ll, n, m, q);
    vl a(n); re(a);
    vl b(m); re(b);
    vpl queries(q); re(queries);
    dbg(n, m, q);
    dbg(a);
    dbg(b);
    dbg(queries);
    vb response = slv(n, m, q, a, b, queries);
    dbg(response);
    for(auto ok: response) cout << (ok?"YA":"TIDAK") << "\n";
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
        RAYA;
        RAYA;
        RAYA;
        RAYA;
        ll n = rng_ll(1, 10);
        ll m = rng_ll(1, 10);
        ll q = rng_ll(1, 5);
        vl a(n); iota(all(a), 1LL);
        vl b(m); each(x, b) x = rng_ll(1LL, n);
        vpl queries(q); each(x, queries) { x.f = rng_ll(1, m), x.s = rng_ll(1, n); }
        dbg(n, m);
        dbg(a);
        dbg(b);
        dbg("Brute");
        vb ans = brute(n, m, q, a, b, queries);
        dbg("/Brute");
        dbg("Greedy");
        vb greedy = slv(n, m, q, a, b, queries);
        dbg("/Greedy");
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
