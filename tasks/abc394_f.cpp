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
        //* Small-To-Large Merging
		e[x] += e[y]; e[y] = x; return 1;
	}
};

/**tcT> T kruskal(int N, vector<pair<T,pi>> ed) {
	sort(all(ed));
	T ans = 0; DSU D; D.init(N); // edges that unite are in MST
	each(a,ed) if (D.unite(a.s.f,a.s.s)) ans += a.f;
	return ans;
}*/

//* /Template

int bfs_brute(int n, vpi edges) {
    if(n == 1) return 1;
    int ans = 0;
    for(int mask = 1; mask < (1 << n); mask++) {
        set<int> nodes;
        for(int i = 0; i < n; i++)
            if(mask & (1 << i))
                nodes.emplace(i);

        DSU dsu; dsu.init(n);
        vi degree(n);
        for(auto& [u, v]: edges) {
            if(nodes.count(u) && nodes.count(v)) {
                dsu.unite(u, v);
                degree[u]++;
                degree[v]++;
            }
        }

        bool ok = true;
        for(auto& u: nodes) ok &= (dsu.get(u) == dsu.get(*nodes.begin()));
        if(!ok) continue;

        bool ok2 = true;
        for(auto& u: nodes) {
            if(degree[u] > 4) ok2 = false;
        }
        if(ok2) ckmax(ans, __builtin_popcount(mask));
    }
    return ans;
}

int brute(int n, vpi edges) {
    if(n == 1) return -1;
    int ans = 0;
    for(int mask = 1; mask < (1 << n); mask++) {
        set<int> nodes;
        for(int i = 0; i < n; i++)
            if(mask & (1 << i))
                nodes.emplace(i);

        DSU dsu; dsu.init(n);
        vi degree(n);
        for(auto& [u, v]: edges) {
            if(nodes.count(u) && nodes.count(v)) {
                dsu.unite(u, v);
                degree[u]++;
                degree[v]++;
            }
        }

        bool ok = true;
        for(auto& u: nodes) ok &= (dsu.get(u) == dsu.get(*nodes.begin()));
        if(!ok) continue;

        bool ok2 = true;
        bool four = false;
        for(auto& u: nodes) {
            if(degree[u] == 4) four = true;
            else ok2 &= (degree[u] == 1);
        }
        ok2 &= four;
        if(ok2) ckmax(ans, __builtin_popcount(mask));
    }
    if(ans == 0) ans = -1;
    return ans;
}

const int INF = int(1e9) + 5;
int bfs(vi& start, set<int>& nodes, vvi& adj) {
    //* dbg("/start");
    //* for(auto& x: start) dbg(x + 1);
    //* dbg("/start");
    map<int, int> degree;
    for(auto& x: nodes) degree[x] = 0;
    {
        map<int, int> vis;
        auto dfs = [&](auto&& self, int src) {
            if(vis[src]) return;
            vis[src] = true;
            for(auto& nxt: adj[src]) {
                if(nodes.count(nxt) && !vis[nxt]) {
                    degree[src]++;
                    degree[nxt]++;
                    self(self, nxt);
                }
            }
        }; dfs(dfs, *nodes.begin());
    }
    set<pi> ms;
    for(auto& x: nodes) ms.emplace(degree[x], x);
    //* dbg(ms);
    map<int, int> vis;
    map<int, int> dp;
    int ans = 0;
    while(!ms.empty()) {
        auto it = *ms.begin(); safeErase(ms, it);
        auto [currentDegree, src] = it;
        //* dbg(currentDegree, src + 1, degree[src]);
        if(vis[src]) continue;
        vis[src] = true;
        chk(currentDegree <= 1);

        vi arr;
        for(auto& nxt: adj[src]) {
            if(nodes.count(nxt) && vis[nxt]) {
                arr.eb(dp[nxt]);
            }
        }
        sort(rall(arr));
        if(sz(arr) >= 4) {
            int local_ans = 1;
            for(int i = 0; i < 4; i++)
                local_ans += arr[i];
            ckmax(ans, local_ans);
        }
        dp[src] = 1;
        for(int i = 0; i < min(3, sz(arr)); i++) {
            dp[src] += arr[i];
        }
        ckmax(ans, dp[src]);

        for(auto& nxt: adj[src]) {
            if(nodes.count(nxt) && !vis[nxt]) {
                degree[nxt]--;
                ms.emplace(degree[nxt], nxt);
            }
        }
    }
    return ans;
}

int slv(int n, vpi edges) {
    if(n == 1) return -1;
    vvi adj(n);
    for(auto& [u, v]: edges) {
        adj[u].eb(v);
        adj[v].eb(u);
    }

    int ans = 0;
    vi degree(n);
    for(auto& [u, v]: edges) {
        degree[u]++;
        degree[v]++;
    }
    vb isGood(n);
    for(int u = 0; u < n; u++)
        isGood[u] = (degree[u] >= 4);

    vb already(n);
    vi component_degree(n);
    for(int u = 0; u < n; u++) {
        if(isGood[u] && !already[u]) {
            set<int> nodes;
            auto dfs = [&](auto&& self, int src) -> void {
                already[src] = true;
                nodes.emplace(src);

                for(auto& nxt: adj[src]) {
                    if(isGood[nxt] && !already[nxt]) {
                        component_degree[src]++;
                        component_degree[nxt]++;
                        self(self, nxt);
                    }
                }
            }; dfs(dfs, u);
            vi start;
            for(auto& x: nodes)
                if(component_degree[x] <= 1)
                    start.eb(x);
            dbg(start, nodes);
            ckmax(ans, bfs(start, nodes, adj));
        }
    }
    dbg(ans);


    if(ans == 0) return -1;
    ans = 5 + (ans - 1) * 3;
    return ans;
}

void solve() {
    int n; cin >> n;
    vpi edges(n - 1);
    for(auto& [u, v]: edges) {
        cin >> u >> v;
        u--; v--;
    }
    int response = slv(n, edges);
    cout << response << "\n";

    if(isDebugging) {
        int ans = brute(n, edges);
        dbg(ans, response);
        chk(ans == response);
    }
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
    //* suppose that this tree has all nodes with degree >= 4
    while(0) {
        RAYA;
        int n = rng_int(1, 19);
        vpi edges = treeRand(n, rng_int(5, n + 5));
        dbg(n);
        dbg(edges);
        //* for(auto& [u, v]: edges) cout << (u + 1) << " " << (v + 1) << "\n";

        int ans = bfs_brute(n, edges);
        int greedy = -INF;
        {
            vi degree(n); for(auto& [u, v]: edges) { degree[u]++; degree[v]++; }
            vi start; for(int u = 0; u < n; u++) if(degree[u] == 1) start.eb(u);
            set<int> nodes; for(int u = 0; u < n; u++) nodes.emplace(u);
            vvi adj(n); for(auto& [u, v]: edges) { adj[u].eb(v); adj[v].eb(u); }
            greedy = bfs(start, nodes, adj);
        }
        dbg(ans, greedy);
        if(ans != greedy) {
            for(auto& [u, v]: edges) cout << (u + 1) << " " << (v + 1) << "\n";
            chk(ans == greedy);
        }
    }

    while(0) {
        RAYA;
        int n = rng_int(1, 20);
        vpi edges = treeRand(n, rng_int(0, n + 5));
        dbg(n);
        dbg(edges);

        int ans = brute(n, edges);
        int greedy = slv(n, edges);
        dbg(ans, greedy);
        if(ans != greedy) {
            for(auto& [u, v]: edges) cout << (u + 1) << " " << (v + 1) << "\n";
            chk(ans == greedy);
        }
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
