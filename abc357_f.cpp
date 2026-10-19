#ifdef LOCAL
    #ifdef _WIN32
        #define WIN32_LEAN_AND_MEAN
        #define NOMINMAX
        #include <windows.h>
        #include <psapi.h>
    #else
        #include <sys/resource.h>
    #endif
#endif




//* sometimes pragmas don't work, if so, just comment it!
#pragma GCC optimize ("Ofast")
//! #pragma GCC optimize ("trapv")

#include <bits/stdc++.h> //? if you don't want IntelliSense
using namespace std;

#undef _GLIBCXX_DEBUG //? for Stress Testing
#pragma GCC target ("avx,avx2")



//* Debugger
void print_memory_usage() {
#ifdef LOCAL
    #ifdef _WIN32
        PROCESS_MEMORY_COUNTERS pmc;
        if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
            long double block = 1024;
            long double taken = pmc.PeakWorkingSetSize / (block * block);

            std::cerr << "\n";
            std::cerr << "\033[42m++++++++++++++++++++\033[0m\n";
            std::cerr << "\033[42m[Memory] Peak Working Set: "
            << taken << " MB\033[0m\n";
            std::cerr << "\033[42m++++++++++++++++++++\033[0m";
        }
    #else
        struct rusage usage;
        getrusage(RUSAGE_SELF, &usage);
        #ifdef __APPLE__
            double peak_mb = usage.ru_maxrss / (1024.0 * 1024.0); // macOS en Bytes
        #else
            double peak_mb = usage.ru_maxrss / 1024.0;            // Linux en KiB
        #endif
        std::cerr << "[Memory] Peak RSS: " << peak_mb << " MB\n";
    #endif
#endif
}




#ifdef LOCAL
    #include "helpers/debug.h"

    const bool isDebugging = true;
#else
    #define dbg(...)     0
    #define chk(...)     0
    #define RAYA         0

    const bool isDebugging = false;
#endif
//* /Debugger



using ll = long long;
using db = long double; // or double if tight TL
using str = string;

//? priority_queue for minimum
template<class T> using pqg = priority_queue<T, vector<T>, greater<T>>;

using ull  = unsigned long long;
//? using i64  = long long;
//? using u64  = uint64_t;
//? using i128 = __int128;
//? using u128 = __uint128_t;
//? using f128 = __float128;



using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<db, db>;
#define mp make_pair
#define f  first
#define s  second



#define tcT template<class T
#define tcTU tcT, class U

tcT> using V = vector<T>;
tcT, size_t SZ> using AR = array<T,SZ>;
using vi = V<int>;
using vb = V<bool>;
using vl = V<ll>;
using vd = V<db>;
using vs = V<str>;
using vpi = V<pi>;
using vpl = V<pl>;
using vpd = V<pd>;

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



const int MOD = 998244353;
const int INF = int(1e9) + 5;
const ll BIG = ll(1e18) + 5;
const db PI = acos((db)-1);
const int dx4[4]{1, 0, -1, 0}, dy4[4]{0, 1, 0, -1};  //? for every grid problem!!
mt19937 rng(0); // or mt19937_64
//* mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());



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



void setIn(string s) { freopen(s.c_str(), "r", stdin); }
void setOut(string s) { freopen(s.c_str(), "w", stdout); }

const auto beg_time = std::chrono::high_resolution_clock::now();
double time_elapsed() {
	return chrono::duration<double>(std::chrono::high_resolution_clock::now() -
	                                beg_time)
	    .count();
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

const int dx8[8]{1, 0, -1,  0, 1,  1, -1, -1};
const int dy8[8]{0, 1,  0, -1, 1, -1,  1, -1};

using vvi = V<vi>;
using vvl = V<vl>;
using vvb = V<vb>;

template <typename T>
T custom_abs(T x) {
    if(x < T(0)) return -x;
    return +x;
}

template <typename T>
T custom_sqrt(T x) {
    T r = sqrtl(x);
    while((r + T(1)) * (r + T(1)) < x) r++;
    while(r * r > x) r--;
    return r;
}
//? /Custom Helpers




// return int in [L,R] inclusive
int rng_int(int L, int R) { assert(L <= R);
    return uniform_int_distribution<int>(L,R)(rng);
}

ll rng_ll(ll L, ll R) { assert(L <= R);
    return uniform_int_distribution<ll>(L,R)(rng);
}

// return double in [L,R] inclusive
db rng_db(db L, db R) { assert(L <= R);
    return uniform_real_distribution<db>(L,R)(rng);
}

template<class T> void shuf(vector<T>& v) { shuffle(all(v),rng); }

// generate edges of tree with verts [0,N-1]
// smaller back -> taller tree
vpi treeRand(int N, int back) {
    assert(N >= 1 && back >= 0); vpi ed;
    FOR(i,1,N) ed.eb(i,i-1-rng_int(0,min(back,i-1)));
    return ed;
}




//* Template

/**
 * Description: modular arithmetic operations
 * Source:
 * KACTL
 * https://codeforces.com/blog/entry/63903
 * https://codeforces.com/contest/1261/submission/65632855 (tourist)
 * https://codeforces.com/contest/1264/submission/66344993 (ksun)
 * also see https://github.com/ecnerwala/cp-book/blob/master/src/modnum.hpp
 * (ecnerwal) Verification: https://open.kattis.com/problems/modulararithmetic
 */

template <int MOD, int RT> struct mint {
	static const int mod = MOD;
	static constexpr mint rt() { return RT; }  // primitive root for FFT
	int v;
	explicit operator int() const {
		return v;
	}  // explicit -> don't silently convert to int
	mint() : v(0) {}
	mint(ll _v) {
		v = int((-MOD < _v && _v < MOD) ? _v : _v % MOD);
		if (v < 0) v += MOD;
	}
	bool operator==(const mint &o) const { return v == o.v; }
	friend bool operator!=(const mint &a, const mint &b) { return !(a == b); }
	friend bool operator<(const mint &a, const mint &b) { return a.v < b.v; }
	friend istream &operator>>(istream &is, mint &a) {
		ll x;
		is >> x;
		a = mint(x);
		return is;
	}
	friend ostream &operator<<(ostream &os, mint a) {
		os << int(a);
		return os;
	}

	mint &operator+=(const mint &o) {
		if ((v += o.v) >= MOD) v -= MOD;
		return *this;
	}
	mint &operator-=(const mint &o) {
		if ((v -= o.v) < 0) v += MOD;
		return *this;
	}
	mint &operator*=(const mint &o) {
		v = int((ll)v * o.v % MOD);
		return *this;
	}
	mint &operator/=(const mint &o) { return (*this) *= inv(o); }
	friend mint pow(mint a, ll p) {
		mint ans = 1;
		assert(p >= 0);
		for (; p; p /= 2, a *= a)
			if (p & 1) ans *= a;
		return ans;
	}
	friend mint inv(const mint &a) {
		assert(a.v != 0);
		return pow(a, MOD - 2);
	}

	mint operator-() const { return mint(-v); }
	mint &operator++() { return *this += 1; }
	mint &operator--() { return *this -= 1; }
	friend mint operator+(mint a, const mint &b) { return a += b; }
	friend mint operator-(mint a, const mint &b) { return a -= b; }
	friend mint operator*(mint a, const mint &b) { return a *= b; }
	friend mint operator/(mint a, const mint &b) { return a /= b; }
};

using mi = mint<MOD, 5>;  // 5 is primitive root for both common mods
using vmi = V<mi>;
using pmi = pair<mi, mi>;
using vpmi = V<pmi>;







/**
 * Description: Square root decomposition for range sum. The array is cut into blocks of
 *   block_size consecutive positions and every block keeps the sum of what it holds, so a
 *   point update touches one block and a range query adds the whole blocks in the middle
 *   plus the leftovers at the two ends. Values are int, the sums are long long.
 * Time: O(n) build, O(1) update, O(sqrt(n)) query
 * Source: https://usaco.guide/plat/sqrt
 * Verification: TODO
 * API: ranges are inclusive and zero indexed, and must be valid, 0 <= l <= r < n.
 *     Sqrt s(a)         block_size becomes ceil(sqrt(n)), the usual choice
 *     Sqrt s(bs, a)     your own block_size, anything from 1 to n works
 *     s.update(p, v)    a[p] = v
 *     s.query(r)        sum of a[0..r]
 *     s.query(l, r)     sum of a[l..r]
 *   The range query is two prefixes, query(r) minus query(l - 1), which is allowed because a
 *   sum can be subtracted. It walks the blocks twice instead of once, measured at 1.2 to 1.4
 *   times the cost of going straight from l to r, and in exchange it is three lines. An
 *   operation with no inverse, a minimum for instance, could not do this and would need the
 *   single pass. The asserts cost nothing measurable: none of them sits inside a loop.
 * Example, point assignment and range sum:
 *   int n, q; cin >> n >> q;
 *   vector<int> a(n);
 *   for (int& x : a) cin >> x;
 *   Sqrt s(a);
 *   while (q--) {
 *       int type; cin >> type;
 *       if (type == 1) { int p, v; cin >> p >> v; s.update(p, v); }
 *       else { int l, r; cin >> l >> r; cout << s.query(l, r) << "\n"; }
 *   }
 */

struct Sqrt {
    int n;
    int block_size;
    int needed_blocks;
    vmi A, B;
    vmi blocks_sum_ab;
    vmi blocks_sum_a, blocks_sum_b;
    vmi blocks_add_a, blocks_add_b;

    Sqrt(int _n, int sqrtn, vmi& _A, vmi& _B): block_size(sqrtn) {
        n = _n;
        block_size = sqrtn;
        A = _A;
        B = _B;

        chk(n >= 1);
        chk(block_size >= 1);

        needed_blocks = (n + block_size - 1) / block_size; // ceil(n / block_size)
        blocks_sum_ab.assign(needed_blocks, 0);
        blocks_sum_a.assign(needed_blocks, 0);
        blocks_sum_b.assign(needed_blocks, 0);
        blocks_add_a.assign(needed_blocks, 0);
        blocks_add_b.assign(needed_blocks, 0);

        for(int i = 0; i < n; i++) {
            int id = bid(i);
            blocks_sum_ab[id] += A[i] * B[i];
            blocks_sum_a[id] += A[i];
            blocks_sum_b[id] += B[i];
        }
    }

    int bid(int i) const {
        chk(block_size >= 1); // no dividir entre cero
        int b = i / block_size;
        chk(0 <= b && b < needed_blocks);   // no desbordar blocks
        return b;
    }




    void update_block(int id, int inc, bool change_a) {
        if(change_a) {
            blocks_add_a[id] += inc;
        } else {
            blocks_add_b[id] += inc;
        }
    }

    void update_single(int i, int inc, bool change_a) {
        int id = bid(i);

        blocks_sum_ab[id] -= A[i] * B[i];

        if(change_a) {
            blocks_sum_a[id] -= A[i];
            A[i] += inc;
            blocks_sum_a[id] += A[i];
        } else {
            blocks_sum_b[id] -= B[i];
            B[i] += inc;
            blocks_sum_b[id] += B[i];
        }

        blocks_sum_ab[id] += A[i] * B[i];
    }


    /** O(sqrt(n)) query of [0, r] */
    void range_update(int r, int d, bool change_a) {
        dbg("Range Update", r, d, change_a);
        assert(0 <= r && r < n);

        const int b = bid(r);

        for (int i = 0; i < b; i++) { // bloques enteros antes del de r
            dbg("Update block", i);
            update_block(i, d, change_a);
        }

        for (int i = b * block_size; i <= r; i++) { // lo que queda dentro del bloque de r
            dbg("Update single", i);
            update_single(i, d, change_a);
        }
    }

    /** O(sqrt(n)) query for sum of [l, r] */
    void range_update(int l, int r, int d, bool change_a) {
        assert(0 <= l && l <= r && r < n);

        range_update(r, +d, change_a);
        if(l) range_update(l - 1, -d, change_a);
    }

    /** O(sqrt(n)) query of [0, r] */
    mi query(int r) const {
        assert(0 <= r && r < n);

        const int b = bid(r);

        mi res = 0;
        for (int i = 0; i < b; i++) { // bloques enteros antes del de r
            dbg("query block", i);
            res += blocks_sum_ab[i];
            res += blocks_add_b[i] * blocks_sum_a[i];
            res += blocks_add_a[i] * blocks_sum_b[i];
            res += blocks_add_a[i] * blocks_add_b[i] * mi(block_size);
        }

        for (int i = b * block_size; i <= r; i++) { // lo que queda dentro del bloque de r
            dbg("query single", i, A[i], B[i], blocks_add_a[b], blocks_add_b[b]);
            res += (A[i] + blocks_add_a[b]) * (B[i] + blocks_add_b[b]);
        }

        return res;
    }

    int query(int l, int r) const {
        assert(0 <= l && l <= r && r < n);
        mi res = query(r) - (l == 0 ? 0 : query(l - 1));
        return int(res);
    }
};

//* /Template

void solve() {
    // run A < A3.in
    // xd A < A4.in

    int n, q; cin >> n >> q;
    dbg(n, q);
    vmi a(n), b(n);

    dbg("a");
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        a[i] = x;
        dbg(x);
    }
    dbg("b");
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        b[i] = x;
        dbg(x);
    }

    Sqrt st(n, custom_sqrt(n), a, b);
    dbg(st.block_size);


    rep(q) {
        RAYA;
        int type; cin >> type;

        if(type == 1) {
            int l, r, d; cin >> l >> r >> d; l--; r--;
            dbg("Add d to A", type, l, r, d);

            st.range_update(l, r, d, true);
        } else if(type == 2) {
            int l, r, d; cin >> l >> r >> d; l--; r--;
            dbg("Add d to B", type, l, r, d);

            st.range_update(l, r, d, false);
        } else {
            int l, r; cin >> l >> r; l--; r--;

            dbg("Query", type, l, r);

            int res = st.query(l, r);
            dbg(res);
            cout << res << "\n";
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    if(isDebugging) {
        dbg("debug");
        // setIn("xd.in");
    }

    int t = 1;
    // cin >> t;
    while(t--) {
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

        print_memory_usage();
    #endif
}
