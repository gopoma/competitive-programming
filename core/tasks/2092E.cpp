//* sometimes pragmas don't work, if so, just comment it!
#pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
// #pragma GCC optimize ("trapv")

#undef _GLIBCXX_DEBUG //? for Stress Testing

#include <bits/stdc++.h>
using namespace std;



//* Debugger
string to_string(string s) {
    return '"' + s + '"';
}

string to_string(const char* s) {
    return to_string((string) s);
}

string to_string(char c) {
    return string(1, c);
}

string to_string(bool b) {
    return (b ? "true" : "false");
}

template <typename A>
string to_string(A v);

string to_string(vector<bool> v) {
    bool first = true;
    string res = "[";
    for (auto x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += x ? "true" : "false";
    }
    res += "]";
    return res;
}

template <typename A, typename B>
string to_string(pair<A, B> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}


template <typename A>
string to_string(A v) {
    bool first = true;
    string res = "[";
    for (const auto &x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(x);
    }
    res += "]";
    return res;
}



void debug_out() { cerr << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}



#ifdef LOCAL
const vector<string> __C_DBG{
    "\033[1;34m",
    "\033[0;32m = \033[35m",
    "\033[0m",
    "]\033[35m:",
    "\033[101m",
    "\033[0m"
};

#define MACRO(code) do {code} while (false)

#define dbg(x)      MACRO(  \
    auto xd = x;    \
    cerr << "Line(" << __LINE__ << "): " << __C_DBG[0] << #x << __C_DBG[1] << to_string(xd) << __C_DBG[2] << endl;  \
)



#define dbg(...)    MACRO(  \
    cerr << "Line(" << __LINE__ << "): " << __C_DBG[0] << "[" << #__VA_ARGS__ << __C_DBG[3];    \
    debug_out(__VA_ARGS__);     \
    cerr << __C_DBG[2];     \
)

#define GA          dbg(0)
// RAYA tiene 32 caracteres "="
#define RAYA        cerr << __C_DBG[4] << "================================" << __C_DBG[5] << endl;

const bool isDebugging = true;
#else
#define dbg(x)
#define dbg(...)
#define GA
#define RAYA

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
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};  //? for every grid problem!!
mt19937 rng(0); // or mt19937_64
// mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());



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

const int dddx[8]{1, 0, -1,  0, 1,  1, -1, -1};
const int dddy[8]{0, 1,  0, -1, 1, -1,  1, -1};

using vvi = V<vi>;
using vvl = V<vl>;
using vvb = V<vb>;
//? /Custom Helpers



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

ll custom_abs(ll x) {
    if(x < 0) return -x;
    return +x;
}
//* /Template






using Info = tuple<ll, ll, ll>;
int brute(ll n, ll m, V<Info> restrictions) {
    const ll tot = n * m;
    ll total_options = 0;




    vi count_sames(2);
    vi count_diffs(2);
    V<vvi> goods;
    for(int mask = 0; mask < (1 << tot); mask++) {
        bool ok = true;
        for(auto& [i, j, color]: restrictions) {
            bool a = mask & (1 << (i * m + j));
            bool b = color;

            if(a != b) {
                ok = false;
            }
        }
        if(!ok) continue;





        total_options++;

        vvi G(n, vi(m));

        for(int i = 0; i < tot; i++) {
            if(mask & (1 << i)) {
                const int row = i / m;
                const int col = i % m;

                G[row][col] = +1;
            }
        }

        int sames = 0;
        int diffs = 0;
        for(int i1 = 0; i1 < n; i1++) {
            for(int i2 = 0; i2 < n; i2++) {
                for(int j1 = 0; j1 < m; j1++) {
                    for(int j2 = 0; j2 < m; j2++) {
                        if(i1 + j1 < i2 + j2) {
                            int d = abs(i1 - i2);
                            int d2 = abs(j1 - j2);
                            if(d + d2 == 1) {
                                if(G[i1][j1] == G[i2][j2]) {
                                    sames++;
                                } else {
                                    diffs++;
                                }
                            }
                        }
                    }
                }
            }
        }

        // RAYA;
        // for(auto& x: G) dbg(x);
        // dbg(sames, diffs);

        if(diffs & 1) {
            goods.emplace_back(G);
        }

        count_sames[sames & 1]++;
        count_diffs[diffs & 1]++;
    }

//    RAYA;
//    RAYA;
//    RAYA;
//    RAYA;
//    RAYA;
//    RAYA;
//    RAYA;

//    dbg("Goods");
//    for(auto& good: goods) {
//        for(auto& x: good) {
//            dbg(x);
//        }
//        RAYA;
//    }

//    RAYA;
//    RAYA;
//    RAYA;
//
//    dbg(n, m, tot);
//    dbg("Total", (1 << tot));
//    dbg("Total Options", total_options);
//    // dbg("Sames");
//    // dbg("Evens", count_sames[0]);
//    // dbg("Odds", count_sames[1]);
//    dbg("Diffs");
//    dbg("Evens", count_diffs[0]);
//    dbg("Odds", count_diffs[1]);
    return count_diffs[0];
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
struct custom_hash {
	static uint64_t splitmix64(uint64_t x) {
		// http://xorshift.di.unimi.it/splitmix64.c
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}

	size_t operator()(pair<uint64_t,uint64_t> x) const {
		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x.first + FIXED_RANDOM)^(splitmix64(x.second + FIXED_RANDOM) >> 1);
	}
};
struct chash { // To use most bits rather than just the lowest ones:
	const uint64_t C = ll(4e18 * acos(0)) | 71; // large odd number
	ll operator()(ll x) const { return __builtin_bswap64((x^RANDOM)*C); }
};
//?__gnu_pbds::gp_hash_table<ll, int, chash> h({},{},{},{}, {1 << 16});

template <typename K, typename V, typename Hash = chash>
using hash_map = __gnu_pbds::gp_hash_table<K, V, Hash>;

template <typename K, typename Hash = chash>
using hash_set = hash_map<K, __gnu_pbds::null_type, Hash>;


void slv(ll n, ll m, ll k, V<Info> cells) {
    if(isDebugging && sz(cells) <= 25) {
        for(auto& [i, j, c]: cells) {
            dbg(i, j, c);
        }
    }




    // run A < A3.in
    // xd A < A4.in
    hash_map<int, hash_map<int, int>> info_color;
    for(auto& [x, y, c]: cells) {
        // dbg(x, y, c);
        info_color[x][y] = c;
    }




    auto inBounds = [&](int i, int j) -> bool {
        return (0 <= i && i < n) && (0 <= j && j < m);
    };








    // set all green cells to 0 (black)
    auto there = [&](int i, int j) -> bool {
        return (info_color.find(i) != info_color.end()) && (info_color[i].find(j) != info_color[i].end());
    };
    auto getColor = [&](int i, int j) -> int {
        if(!there(i, j)) return 0;
        return info_color[i][j];
    };










    auto check = [&](int i, int j) -> bool {
        if(there(i, j)) return false;
        int count = 0;
        for(int id = 0; id < 4; id++) {
            int ni = i + dx[id];
            int nj = j + dy[id];

            if(inBounds(ni, nj) && !there(ni, nj)) {
                count++;
            }
        }
        return count == 3;
    };




    vpi candidates;
    for(int j = 0; j < m; j++) {
        // i = 0
        if(check(0, j)) {
            candidates.emplace_back(0, j);
            break;
        }

        // i = n - 1
        if(check(n - 1, j)) {
            candidates.emplace_back(n - 1, j);
            break;
        }
    }
    for(int i = 0; candidates.empty() && i < n; i++) {
        // j = 0
        if(check(i, 0)) {
            candidates.emplace_back(i, 0);
            break;
        }

        // j = m - 1
        if(check(i, m - 1)) {
            candidates.emplace_back(i, m - 1);
            break;
        }
    }
    // dbg("Before", candidates);



    for(auto& [i, j, color]: cells) {
        candidates.emplace_back(i, j);

        for(int id = 0; id < 4; id++) {
            const int ni = i + dx[id];
            const int nj = j + dy[id];

            if(inBounds(ni, nj)) {
                candidates.emplace_back(ni, nj);
            }
        }
    }
    dbg(sz(candidates));
    remDup(candidates);
    dbg(sz(candidates));





    mi response;
    bool par = false;
    int diffs = 0;
    for(auto& [i, j]: candidates) {
        {
            // right
            if(inBounds(i, j + 1)) {
                diffs += getColor(i, j) != getColor(i, j + 1);
            }
            // down
            if(inBounds(i + 1, j)) {
                diffs += getColor(i, j) != getColor(i + 1, j);
            }
        }
        {
            int d = 0;
            for(int id = 0; id < 4; id++) {
                const int ni = i + dx[id];
                const int nj = j + dy[id];
                if(!inBounds(ni, nj)) continue;


                if(getColor(i, j) != getColor(ni, nj)) {
                    d--;
                }
                int flipped = (getColor(i, j) == 0)? 1 : 0;
                if(flipped != getColor(ni, nj)) {
                    d++;
                }
            }
            d = custom_abs(d);
            if(!there(i, j) && (d & 1)) {
                par = true;
            }
        }
    }

    dbg(diffs, par);



    mi total_options = pow(mi(2), n * m - k);
    dbg(int(total_options));

    if(par) {
        response = total_options / mi(2);
    } else {
        if(diffs & 1) {
            response = 0;
        } else {
            response = total_options;
        }
    }

    cout << int(response) << "\n";





    if(isDebugging && (n * m <= 25)) {
        int gre = int(response);
        int ans = brute(n, m, cells);
        dbg(gre, ans);
        assert(gre == ans);
    }
}

void solve() {
    ll n, m, k; cin >> n >> m >> k;
    V<Info> cells(k);
    for(auto& [x, y, c]: cells) {
        cin >> x >> y >> c;
        x--; y--;
    }

    dbg(n, m, k);

    slv(n, m, k, cells);
}



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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    while(isDebugging && 1) {
        RAYA;
        RAYA;
        RAYA;

        ll n, m;
        if(true) {
            n = rng_ll(int(1e9) - 500, int(1e9));
            m = rng_ll(int(1e9) - 500, int(1e9));
        } else {
            n = rng_int(3, 4);
            m = rng_int(4, 5);
        }





        V<Info> restrictions;
        ll iter = min(rng_ll(1, 4 * n * m), ll(2e5));
        set<pl> aux;
        rep(iter) {
            ll i = rng_ll(0, n - 1);
            ll j = rng_ll(0, m - 1);
            ll c = rng_ll(0, 1);
            if(aux.count({i, j})) {
                continue;
            }
            restrictions.emplace_back(i, j, c);
            aux.emplace(i, j);
        }
        int k = sz(restrictions);





        dbg(n, m, k);
        db st = time_elapsed();
        slv(n, m, k, restrictions);
        db nd = time_elapsed();
        db taken = nd - st;
        dbg(taken);
        if(1 && taken > db(2)) {
            assert(false);
        }

    }

    if(isDebugging && 0) {
        setIn("2092E.in");
    }

    int t = 1;
    cin >> t;
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
    #endif
}
