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
//? #pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

//! #undef _GLIBCXX_DEBUG //? for Stress Testing


#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <climits>
#include <cmath>
#include <complex>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <vector>
using namespace std;




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



const int MOD = int(1e9) + 7;
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

ll custom_abs(ll x) {
    if(x < 0) return -x;
    return +x;
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
 * Description: Faster 1D range minimum query.
 * Source: KACTL
 * Verification:
	* https://judge.yosupo.jp/submission/126814
 * Memory: O(N\log N)
 * Time: O(1)
 */

tcT, size_t SZ> struct RMQ { // floor(log_2(x))
	static constexpr int level(int x) { return 31-__builtin_clz(x); }
	array<array<T,SZ>, level(SZ)+1> jmp;
	T cmb(T a, T b) { return min(a, b); }
	void init(const V<T>& v) { assert(sz(v) <= SZ);
		copy(all(v), begin(jmp[0]));
		for (int j = 1; 1<<j <= sz(v); ++j) {
			F0R(i,sz(v)-(1<<j)+1) jmp[j][i] = cmb(jmp[j-1][i],
				jmp[j-1][i+(1<<(j-1))]);
		}
	}
	T query(int l, int r) {
		assert(l <= r); int d = level(r-l+1);
		return cmb(jmp[d][l],jmp[d][r-(1<<d)+1]); }
};

RMQ<ll, int(1e6)> stleft, stright;
//* /Template


/**
 * Description: All-Pairs Shortest Path
 * Source: KACTL
 * Verification:
    * https://open.kattis.com/problems/allpairspath
    * https://cses.fi/problemset/task/1672/
 */

void floydWarshall(V<vl>& m) {
    int n = sz(m);
    F0R(i,n) ckmin(m[i][i], 0LL);
    F0R(k,n) F0R(i,n) F0R(j,n)
        if (m[i][k] != BIG && m[k][j] != BIG) {
            auto newDist = max(m[i][k]+m[k][j],-BIG);
            ckmin(m[i][j],newDist);
        }
    F0R(k,n) if (m[k][k] < 0) F0R(i,n) F0R(j,n)
        if (m[i][k] != BIG && m[k][j] != BIG) m[i][j] = -BIG;
}

vl brute(ll n, vl a, vl b, ll q, vpl que) {
    vvl dist(n + 1, vl(n + 1, BIG));
    for(int i = 0; i < n; i++) {
        int u = i;
        int v = (i + 1) % n;

        ckmin(dist[u][v], a[i]);
        ckmin(dist[v][u], a[i]);
    }
    for(int i = 0; i < n; i++) {
        int u = i;
        int v = n;

        ckmin(dist[u][v], b[i]);
        ckmin(dist[v][u], b[i]);
    }

    floydWarshall(dist);
    vl res;
    for(auto& [u, v]: que) {
        res.eb(dist[u][v]);
    }
    return res;
}

void slv(ll n, vl a, vl b, ll q, vpl que) {
    vl pleft(2 * n);
    vl costleft(2 * n);
    for(ll i = 1; i < 2 * n; i++) {
        pleft[i] += pleft[i - 1];
        pleft[i] += a[(i - 1) % n];

        costleft[i] = pleft[i] + b[i % n];
    }
    vl pright(2 * n);
    vl costright(2 * n);
    for(ll i = 2 * n - 2; i >= 0; i--) {
        pright[i] += pright[i + 1];
        pright[i] += a[i % n];

        costright[i] = pright[i] + b[i % n];
    }
    costleft.ft = b.ft;
    costright.bk = b.bk;
    stleft.init(costleft);
    stright.init(costright);
    dbg(pleft);
    dbg(pright);

    auto unicost = [&](ll u) -> ll {
        ll re = BIG;
        ckmin(re, stleft.query(u, 2 * n - 1) - pleft[u]);
        ckmin(re, stright.query(0, u + n) - pright[u + n]);
        return re;
    };

    auto cost = [&](ll u, ll v) -> ll {
        ll xx = unicost(u);
        ll yy = unicost(v);

        ll cotravel = xx + yy;

        if(u > v) v += n;
        ll conormal = pleft[v] - pleft[u];
        dbg(u, v, cotravel, xx, yy, conormal);

        ll re = min(conormal, cotravel);
        return re;
    };

    auto work = [&](ll u, ll v) -> ll {
        if(v == n) {
            return unicost(u);
        } else {
            ll xx = cost(u, v);
            ll yy = cost(v, u);
            return min(xx, yy);
        }
    };

    vl res;
    for(auto& [u, v]: que) {
        // RAYA;
        // RAYA;
        // dbg("Processing", u, v);
        chk(u < v);
        ll lre = work(u, v);
        res.eb(lre);
    }
    for(auto& x: res) cout << x << "\n";

    if(isDebugging) {
        vl ans = brute(n, a, b, q, que);
        dbg(res, ans);
        chk(res == ans);
    }
}

void solve() {
    // run A < A3.in
    // xd A < A4.in

    ll n, q; cin >> n >> q;
    vl a(n); for(auto& x: a) cin >> x;
    vl b(n); for(auto& x: b) cin >> x;
    vpl que(q);
    for(auto& [u, v]: que) {
        cin >> u >> v;
        u--; v--;
    }
    dbg(n, q);
    dbg(a);
    dbg(b);

    slv(n, a, b, q, que);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    while(isDebugging&&1) {
        RAYA;
        RAYA;
        RAYA;

        ll n = rng_ll(1, 6);
        vl a(n), b(n);
        for(auto& x: a) x = rng_ll(1, 5);
        for(auto& x: b) x = rng_ll(1, 5);
        ll q = rng_ll(1, 10);
        vpl que(q);
        for(auto& [u, v]: que) {
            u = rng_ll(0, n - 1);
            v = rng_ll(u + 1, n);
        }
        dbg(n);
        dbg(a);
        dbg(b);
        dbg(q);
        dbg(que);
        slv(n, a, b, q, que);
    }

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
