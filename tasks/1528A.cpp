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
 * Description: Generate various types of trees.
 * Source: Own + Dhruv Rohatgi
 */

////////////// DISTRIBUTIONS

// return int in [L,R] inclusive
int rng_int(int L, int R) { assert(L <= R);
	return uniform_int_distribution<int>(L,R)(rng);  }
ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }

// return double in [L,R] inclusive
db rng_db(db L, db R) { assert(L <= R);
	return uniform_real_distribution<db>(L,R)(rng); }

// http://cplusplus.com/reference/random/geometric_distribution/geometric_distribution/
// flip a coin which is heads with probability p until you flip heads
// mean value of c is 1/p-1
int rng_geo(db p) { assert(0 < p && p <= 1); // p large -> closer to 0
	return geometric_distribution<int>(p)(rng); }

////////////// VECTORS + PERMS

// shuffle a vector
template<class T> void shuf(vector<T>& v) { shuffle(all(v),rng); }

// generate random permutation of [0,N-1]
vi randPerm(int N) { vi v(N); iota(all(v),0); shuf(v); return v; }

// random permutation of [0,N-1] with first element 0
vi randPermZero(int N) { vi v(N-1); iota(all(v),1);
	shuf(v); v.ins(bg(v),0); return v; }

// shuffle permutation of [0,N-1]
vi shufPerm(vi v) {
	int N = sz(v); vi key = randPerm(N);
	vi res(N); F0R(i,N) res[key[i]] = key[v[i]];
	return res;
}

// vector with all entries in [L,R]
vi rng_vec(int N, int L, int R) {
	vi res; F0R(_,N) res.pb(rng_int(L,R));
	return res;
}

// vector with all entries in [L,R], unique
vi rng_vec_unique(int N, int L, int R) {
	set<int> so_far; vi res;
	F0R(_,N) {
		int x; do { x = rng_int(L,R); } while (so_far.count(x));
		so_far.ins(x); res.pb(x);
	}
	return res;
}

////////////// GRAPHS

// relabel edges ed according to perm, shuffle
vpi relabelAndShuffle(vpi ed, vi perm) {
	each(t,ed) {
		t.f = perm[t.f], t.s = perm[t.s];
		if (rng()&1) swap(t.f,t.s);
	}
	shuf(ed); return ed;
}

// shuffle graph with vertices [0,N-1]
vpi shufGraph(int N, vpi ed) { // randomly swap endpoints, rearrange labels
	return relabelAndShuffle(ed,randPerm(N)); }
vpi shufGraphZero(int N, vpi ed) {
	return relabelAndShuffle(ed,randPermZero(N)); }

// shuffle tree given N-1 edges
vpi shufTree(vpi ed) { return shufGraph(sz(ed)+1,ed); }
// randomly swap endpoints, rearrange labels
vpi shufRootedTree(vpi ed) {
	return relabelAndShuffle(ed,randPermZero(sz(ed)+1)); }

void pgraphOne(int N, vpi ed) {
	ps(N,sz(ed));
	each(e,ed) ps(1+e.f,1+e.s);
}

////////////// GENERATING TREES

// for generating tall tree
pi geoEdge(int i, db p) { assert(i > 0);
	return {i,max(0,i-1-rng_geo(p))}; }

// generate edges of tree with verts [0,N-1]
// smaller back -> taller tree
vpi treeRand(int N, int back) {
	assert(N >= 1 && back >= 0); vpi ed;
	FOR(i,1,N) ed.eb(i,i-1-rng_int(0,min(back,i-1)));
	return ed; }

// generate path
vpi path(int N) { return treeRand(N,0); }

// generate tall tree (large diameter)
// the higher the p the taller the tree
vpi treeTall(int N, db p) { assert(N >= 1);
	vpi ed; FOR(i,1,N) ed.pb(geoEdge(i,p));
	return ed; }

// generate tall tree, then add rand at end
vpi treeTallShort(int N, db p) {
	assert(N >= 1); int mid = (N+1)/2;
	vpi ed = treeTall(mid,p);
	FOR(i,mid,N) ed.eb(i,rng_int(0,i-1));
	return ed; }

// lots of stuff connected to either heavy1 or heavy2
vpi treeTallHeavy(int N, db p) {
	assert(N >= 1); // + bunch of rand
	vpi ed; int heavy1 = 0, heavy2 = N/2;
	FOR(i,1,N) {
		if(i < N/4) ed.eb(i,heavy1);
		else if (i > heavy2 && i < 3*N/4) ed.eb(i,heavy2);
		else ed.pb(geoEdge(i,p));
	}
	return ed;
}

// heavy tall tree + random
// lots of verts connected to heavy1 or heavy2
vpi treeTallHeavyShort(int N, db p) {
	assert(N >= 1); // + almost-path + rand
	vpi ed; int heavy1 = 0, heavy2 = N/2;
	FOR(i,1,N) {
		if(i < N/4) ed.eb(i,heavy1);
		else if (i <= heavy2) ed.pb(geoEdge(i,p)); // tall -> heavy1
		else if (i > heavy2 && i < 3*N/4) ed.eb(i,heavy2);
		else ed.eb(i,rng_int(0,i-1));
	}
	return ed;
}

int rand_prime(int l, int r) {
	while(1) {
		int x = rng_int(l,r);
		bool bad = 0;
		for (int i = 2; i*i <= x; ++i) if (x%i == 0) bad = 1;
		if (!bad) return x;
	}
}

/**
 * Description: Hash map with similar API as unordered\_map.
 	* Initial capacity must be a power of 2 if provided.
 * Source: KACTL
 * Memory: \tilde 1.5x unordered map
 * Time: \tilde 3x faster than unordered map
 * API: hash_map<ll, ll> go({},{},{},{}, {1 << 20});
 */

// #include<bits/extc++.h>
#include <ext/pb_ds/assoc_container.hpp>

//? For CodeForces, or other places where hacking might be a problem:

const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash { // To use most bits rather than just the lowest ones:
	const uint64_t C = ll(4e18 * acos(0)) | 71; // large odd number
	ll operator()(ll x) const { return __builtin_bswap64((x^RANDOM)*C); }
};
//?__gnu_pbds::gp_hash_table<ll, int, chash> h({},{},{},{}, {1 << 16});

template <typename K, typename V, typename Hash = chash>
using hash_map = __gnu_pbds::gp_hash_table<K, V, Hash>;

template <typename K, typename Hash = chash>
using hash_set = hash_map<K, __gnu_pbds::null_type, Hash>;
//* /Template

ll brute(int n, vpl limits, vpi tree) {
    chk(n >= 2);
    chk(sz(limits) == n);
    chk(sz(tree) == n - 1);
    for(auto& [u, v]: tree) {
        chk(0 <= u && u < n);
        chk(0 <= v && v < n);
    }

    ll ans = -BIG;
    vector<map<ll, ll>> fino;

    map<ll, ll> keep;
    auto improve = [&](map<ll, ll> mappings, bool check) -> ll {
        ll local_ans = 0;

        for(auto& [u, v]: tree) {
            local_ans += abs(mappings[u] - mappings[v]);
        }

        ;
        if(check && (ckmax(ans, local_ans) || ans == local_ans)) {
            fino.eb(mappings);
        }

        return local_ans;
    };

    function<void(int)> backtrack = [&](int node) {
        if(node == n) {
            improve(keep, true);
            return;
        }

        for(ll val = limits[node].f; val <= limits[node].s; val++) {
            keep[node] = val;

            backtrack(node + 1);
        }
    }; backtrack(0);

    chk(ans != -BIG);

    vector<map<ll, ll>> tmp;
    for(auto& mappings: fino) {
        if(improve(mappings, false) == ans) {
            tmp.eb(mappings);
        }
    }
    fino = tmp;

    bool ok = false;
    for(auto& mappings: fino) {
        bool local_ok = true;

        for(int u = 0; u < n; u++) {
            local_ok &= (mappings[u] == limits[u].f || mappings[u] == limits[u].s);
        }

        ok |= local_ok;
    }
    chk(ok);

    //? dbg("Configurations:");
    //? for(auto& mappings: fino) dbg(mappings);

    return ans;
}

ll solve(int n, vpl limits, vpi tree) {
    chk(n >= 2);
    chk(sz(limits) == n);
    chk(sz(tree) == n - 1);

    vector<vi> adj(n);
    for(auto& [u, v]: tree) {
        adj[u].eb(v);
        adj[v].eb(u);
    }


    const int root = 0;
    //? unordered_map<ll, unordered_map<ll, bool>> vis;
    //? unordered_map<ll, unordered_map<ll, ll>> dp;
    hash_map<ll, hash_map<ll, bool>> vis;
    hash_map<ll, hash_map<ll, ll>> dp;
    function<ll(int, int, ll)> dfs = [&](int u, int p, ll p_val) -> ll {
        if(vis[u][p_val]) return dp[u][p_val];
        vis[u][p_val] = true;

        vl can{limits[u].f, limits[u].s};

        ll ans = 0;
        for(auto& act_val: can) {
            ll local_ans = 0;
            for(auto& v: adj[u]) {
                if(v != p) {
                    local_ans += dfs(v, u, act_val);
                } else {
                    local_ans += abs(act_val - p_val);
                }
            }
            ckmax(ans, local_ans);
        }

        return dp[u][p_val] = ans;
    };
    ll ans = dfs(root, -1, -1);

    return ans;
}


//? Generator
//? /Generator


signed main() {
    setIO();

    while(0) {
        RAYA;
        dbg("go");
        //? int n = rng_int(1, 2e5);
        int n = rng_int(2, 8);
        vpl limits(n); for(auto& x: limits) {
            //? x.f = rng_ll(1, 1e8);
            //? x.s = rng_ll(x.f, 1e9);

            x.f = rng_ll(1, 8);
            x.s = rng_ll(x.f, 10);
        }
        vpi tree = treeRand(n, rng_int(0, n + 1));

        dbg(n);
        dbg(sz(limits), limits);
        dbg(sz(tree), tree);

        ll ans = brute(n, limits, tree);
        ll greedy = solve(n, limits, tree);

        dbg(ans);
        dbg(greedy);

        chk(ans == greedy);
    }

    ll t = 1; re(t);

    FOR(i, 1, t + 1) {
        RAYA;
        RAYA;
        def(int, n);
        vpl limits(n); re(limits);
        vpi tree(n - 1); re(tree);

        dbg(n);
        dbg(limits);
        dbg(tree);

        for(auto& edge: tree) {
            edge.f--;
            edge.s--;
        }

        ll ans = solve(n, limits, tree);
        dbg(ans);
        ps(ans);
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
