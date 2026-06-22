#pragma GCC optimize ("Ofast")
//* #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

#undef _GLIBCXX_DEBUG //* for Stress Testing



#include <bits/stdc++.h>
using namespace std;



// building blocks
using ll = long long;
using db = long double; // or double if tight TL
using str = string;

//* priority_queue for minimum
//* template<class T> using pqg = priority_queue<T, vector<T>, greater<T>>;

//* using ull  = unsigned long long;
//* using i64  = long long;
//* using u64  = uint64_t;
//* using i128 = __int128;
//* using u128 = __uint128_t;
//* using f128 = __float128;



// pairs
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<db, db>;

#define mp make_pair
#define f first
#define s second



#define tcT template<class T
#define tcTU tcT, class U
#define tcTUU tcT, class ...U

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

using vvi = V<vi>;
using vvl = V<vl>;
using vvb = V<vb>;



// vectors
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



// loops
#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define rep(a) F0R(_,a)
#define each(a,x) for (auto& a: x)



// Debugger
//* __int128_t printer
std::ostream& operator<<( std::ostream& dest, __int128_t value ) {
    std::ostream::sentry s(dest);
    if (s) {
        __uint128_t tmp = value < 0 ? -value : value;
        char buffer[128];
        char* d = std::end(buffer);

        do {
            -- d;
            *d = "0123456789"[tmp % 10];
            tmp /= 10;
        } while (tmp != 0);

        if(value < 0) {
            -- d;
            *d = '-';
        }

        int len = int(std::end(buffer) - d);
        if(dest.rdbuf()->sputn(d, len) != len) {
            dest.setstate(std::ios_base::badbit);
        }
    }
    return dest;
}

const string PAIR_LEFT = "(";
const string PAIR_RIGHT = ")";
const string IT_LEFT = "[";
const string IT_RIGHT = "]";
const string PAIR_SEP = ", ";
const string IT_SEP = ", ";



// benq - print any container + pair
template <typename T, typename = void>
struct is_iterable: false_type {};

template <typename T>
struct is_iterable<T,
    void_t<decltype(begin(declval<T>())),
    decltype(end(declval<T>()))>
>: true_type {};



template <typename T>
typename enable_if<
    is_iterable<T>::value &&
    !is_same<T, string>::value, ostream&
>::type operator<<(ostream &cout, T const &v);



template <typename A, typename B>
ostream &operator<<(ostream &cout, pair<A, B> const &p) {
    return cout << PAIR_LEFT << p.f << PAIR_SEP << p.s << PAIR_RIGHT;
}



template <typename T>
typename enable_if<
    is_iterable<T>::value &&
    !is_same<T, string>::value, ostream&
>::type operator<<(ostream &cout, T const &v) {
    cout << IT_LEFT;
    for (auto it = v.begin(); it != v.end();) {
        cout << *it;
        if(++it != v.end()) {
            cout << IT_SEP;
        }
    }
    return cout << IT_RIGHT;
}



template <typename A, typename B>
istream &operator>>(istream &cin, pair<A, B> &p) {
    cin >> p.first;
    return cin >> p.second;
}



template <typename T>
void debug(string s, T x) {
    cerr << "\033[1;34m" << s << "\033[0;32m = \033[35m" << x << "\033[0m\n";
}

template <typename T, typename... Args>
void debug(string s, T x, Args... args) {
    for (int i = 0, b = 0; i < (int)s.size(); i++)
        if (s[i] == '(' || s[i] == '{') {
            b++;
        } else if (s[i] == ')' || s[i] == '}') {
            b--;
        } else if (s[i] == ',' && b == 0) {
            cerr << "\033[1;34m" << s.substr(0, i) << "\033[0;32m = \033[35m" << x << "\033[31m | ";
            debug(s.substr(s.find_first_not_of(' ', i + 1)), args...);
            break;
        }
}



#ifdef LOCAL
    const bool isDebugging = true;

    #define MACRO(code) do {code} while (false)
    #define dbg(...) MACRO(cerr << "Line(" << __LINE__ << "): "; debug(#__VA_ARGS__, __VA_ARGS__);)
    #define chk(...) if (!(__VA_ARGS__)) cerr << "\033[41m" << "Line(" << __LINE__ << ") -> function(" \
	 << __FUNCTION__  << ") -> CHK FAILED: (" << #__VA_ARGS__ << ")" << "\033[0m" << "\n", exit(0);
    #define RAYA MACRO(cerr << "\033[101m" << "================================" << "\033[0m" << endl;)
#else
    const bool isDebugging = false;

    #define dbg(...)     0
    #define chk(...)     0

    #define RAYA         0
#endif



const auto beg_time = std::chrono::high_resolution_clock::now();
double time_elapsed() {
    return chrono::duration<double>(std::chrono::high_resolution_clock::now() - beg_time).count();
}
// /Debugger



//* Helpers
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

tcT > void remDup(vector<T> &v) {  // sort and remove duplicates
	sort(all(v));
	v.erase(unique(all(v)), end(v));
}
tcTU > void safeErase(T &t, const U &u) {
	auto it = t.find(u);
	assert(it != end(t));
	t.erase(it);
}
//* /Helpers

//* Custom Helpers
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
//* /Custom Helpers



const int MOD = 1e9 + 7;
const ll BIG = 1e18;  //? not too close to LLONG_MAX
const db PI = acos((db)-1);

const int dx[4]{1, 0, -1, 0};  //? for every grid problem!!
const int dy[4]{0, 1, 0, -1};  //? for every grid problem!!
//* const int dx[8]{1, 0, -1,  0, 1,  1, -1, -1};  //? for every grid problem!!
//* const int dy[8]{0, 1,  0, -1, 1, -1,  1, -1};  //? for every grid problem!!

mt19937 rng(0); // or mt19937_64
//* mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());



//* Template
/**
 * Description: Disjoint Set Union with path compression
 	* and union by size. Add edges and test connectivity.
 	* Use for Kruskal's or Boruvka's minimum spanning tree.
 * Time: O(\alpha(N))
 * Source: CSAcademy, KACTL
 * Verification: *
 */

 struct DSU {
	vi e; void init(int N) { e = vi(N,-1); }
	int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
	bool sameSet(int a, int b) { return get(a) == get(b); }
	int size(int x) { return -e[get(x)]; }
	bool unite(int x, int y) { // union by size
		x = get(x), y = get(y); if (x == y) return 0;
		if (e[x] > e[y]) swap(x,y);
		e[x] += e[y]; e[y] = x; return 1;
	}
};

/**tcT> T kruskal(int N, vector<pair<T,pi>> ed) {
	sort(all(ed));
	T ans = 0; DSU D; D.init(N); // edges that unite are in MST
	each(a,ed) if (D.unite(a.s.f,a.s.s)) ans += a.f;
	return ans;
    }*/

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

   //* /Template

using Query = tuple<int, int, int>; // type - * - *
vi brute(int n, vi C, int q, V<Query> queries) {
    vi response;
    DSU dsu; dsu.init(n);
    for(auto& [type, par, par2]: queries) {
        if(type == 1) {
            int a, b; a = par; b = par2; a--; b--;
            dsu.unite(a, b);
        } else {
            assert(type == 2);
            int x, y; x = par; y = par2; x--;
            map<int, int> hist;
            for(int i = 0; i < n; i++) {
                if(dsu.get(i) == dsu.get(x)) hist[C[i]]++;
            }
            response.eb(hist[y]);
        }
    }

    return response;
}

const int MAXN = int(2e5) + 5;
map<int, int> hist[MAXN];
struct DSUCustom {
	vi e;
    void init(int N) {
        e = vi(N,-1);
    }
	int get(int x) {
        return e[x] < 0 ? x : e[x] = get(e[x]);
    }
	bool sameSet(int a, int b) {
        return get(a) == get(b);
    }
	int size(int x) {
        return -e[get(x)];
    }
    int query(int x, int y) {
        int p = get(x);
        return (hist[p].find(y) != hist[p].end())? hist[p][y] : 0;
    }
	bool unite(int x, int y) { // union by size
		x = get(x), y = get(y);
        if (x == y) return 0;

		if (e[x] > e[y]) swap(x,y);

        e[x] += e[y];
        e[y] = x;
        for(auto& [val, cnt]: hist[y]) {
            hist[x][val] += cnt;
        }
        return 1;
	}
};

vi slv(int n, vi C, int q, V<Query> queries) {
    for(int i = 0; i < n; i++) {
        hist[i].clear();
        hist[i][C[i]]++;
    }
    DSUCustom dsu; dsu.init(n);
    vi response;
    for(auto& [type, par, par2]: queries) {
        if(type == 1) {
            int a = par;
            int b = par2;
            a--; b--;
            dsu.unite(a, b);
        } else {
            int x = par;
            int y = par2;
            x--;
            response.eb(dsu.query(x, y));
        }
    }
    return response;
}

void solve() {
    int n, q; cin >> n >> q;
    vi C(n); for(auto& x: C) cin >> x;
    V<Query> queries;
    rep(q) {
        int type, par, par2; cin >> type >> par >> par2;
        queries.eb(type, par, par2);
    }
    vi response = slv(n, C, q, queries);
    dbg(response);
    for(auto& x: response) cout << x << "\n";
}



// return int in [L,R] inclusive
int rng_int(int L, int R) { assert(L <= R);
	return uniform_int_distribution<int>(L,R)(rng);  }
ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }

// shuffle a vector
template<class T> void shuf(vector<T>& v) { shuffle(all(v),rng); }

// generate edges of tree with verts [0,N-1]
// smaller back -> taller tree
vpi treeRand(int N, int back) {
	assert(N >= 1 && back >= 0); vpi ed;
	FOR(i,1,N) ed.eb(i,i-1-rng_int(0,min(back,i-1)));
	return ed; }

void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }

int main() {
    cin.tie(0)->sync_with_stdio(0);  // unsync C / C++ I/O streams
	//? cout << fixed << setprecision(12);
    //? cerr << fixed << setprecision(12);
	cin.exceptions(cin.failbit);
	// throws exception when do smth illegal
	// ex. try to read letter into int
    dbg(isDebugging);



    //? Stress Testing
    while(0) {
        RAYA;
        int n = rng_int(1, 1000);
        int q = rng_int(1, 1000);
        vi C(n); for(auto& x: C) x = rng_int(1, n);
        V<Query> queries;
        rep(q) {
            int type = rng_int(1, 2);
            if(type == 1) {
                int a = rng_int(1, n);
                int b = rng_int(1, n);
                queries.eb(type, a, b);
            } else {
                int x = rng_int(1, n);
                int y = rng_int(1, n);
                queries.eb(type, x, y);
            }
        }
        dbg(n, q);
        dbg(C);
        // for(auto& [type, par, par2]: queries) dbg(type, par, par2);
        dbg("Brute");
        vi ans = brute(n, C, q, queries);
        dbg("/Brute");
        dbg("Greedy");
        vi greedy = slv(n, C, q, queries);
        dbg("/Greedy");
        dbg(ans, greedy);
        chk(ans == greedy);
    }


    while(0) {
        RAYA;
        int n = rng_int(int(2e5), int(2e5));
        int q = rng_int(int(2e5), int(2e5));
        vi C(n); for(auto& x: C) x = rng_int(1, n);
        V<Query> queries;
        rep(q) {
            int type = rng_int(1, 2);
            if(type == 1 && rng_int(1, 100) <= 90) {
                int a = rng_int(1, n);
                int b = rng_int(1, n);
                queries.eb(type, a, b);
            } else {
                int x = rng_int(1, n);
                int y = rng_int(1, n);
                queries.eb(type, x, y);
            }
        }
        db last = time_elapsed();
        slv(n, C, q, queries);
        db current = time_elapsed();
        db taken = current - last;
        dbg(taken);
        if(taken > db(2)) chk(false);
    }



    int t = 1; //! cin >> t;
    for(int i = 0; i < t; i++) {
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
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
    #endif
}
