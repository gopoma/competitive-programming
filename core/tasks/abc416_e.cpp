//* sometimes pragmas don't work, if so, just comment it!
#pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

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
    "\033[0m", "]\033[35m:",
    "\033[101m", "\033[0m"
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

using pi = pair<int,int>;
using pl = pair<ll, ll>;
#define mp make_pair
#define f first
#define s second

#define tcT template<class T
tcT> using V = vector<T>;
tcT, size_t SZ> using AR = array<T,SZ>;
using vi = V<int>;
using vl = V<ll>;
using vb = V<bool>;
using vpi = V<pi>;
using vpl = V<pl>;

#define sz(x) int((x).size())
#define all(x) begin(x), end(x)
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

#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define rep(a) F0R(_,a)
#define each(a,x) for (auto& a: x)

const int MOD = 1e9+7;
const int INF = int(1e9) + 5;
const ll BIG = ll(1e18) + 5;
const db PI = acos((db)-1);
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};  //? for every grid problem!!
mt19937 rng(0); // or mt19937_64
//* mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

ll cdiv(ll a, ll b) {
	return a / b + ((a ^ b) > 0 && a % b);
}  // divide a by b rounded up
ll fdiv(ll a, ll b) {
	return a / b - ((a ^ b) < 0 && a % b);
}  // divide a by b rounded down

tcT> bool ckmin(T& a, const T& b) {
	return b < a ? a = b, 1 : 0; } // set a = min(a,b)
tcT> bool ckmax(T& a, const T& b) {
	return a < b ? a = b, 1 : 0; } // set a = max(a,b)

tcT > void remDup(vector<T> &v) {  // sort and remove duplicates
	sort(all(v));
	v.erase(unique(all(v)), end(v));
}

void setIn(string s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }

const auto beg_time = std::chrono::high_resolution_clock::now();
double time_elapsed() {
	return chrono::duration<double>(std::chrono::high_resolution_clock::now() -
	                                beg_time)
	    .count();
}

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



//* Template
//* /Template

ll adj[500 + 1][500 + 1];
ll dist[500 + 1][500 + 1];

void solve() {
    ll n, m; cin >> n >> m;



    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(i == j) {
                adj[i][j] = 0;
                dist[i][j] = 0;
            } else {
                adj[i][j] = BIG;
                dist[i][j] = BIG;
            }
        }
    }



    for(int _ = 0; _ < m; _++) {
        ll A, B, C; cin >> A >> B >> C;

        adj[A][B] = min(adj[A][B], C);
        adj[B][A] = min(adj[B][A], C);

        dist[A][B] = min(dist[A][B], C);
        dist[B][A] = min(dist[B][A], C);
    }



    ll K, T; cin >> K >> T;
    vl D(K);
    vb hasAirport(n + 1);
    for(auto& x: D) cin >> x;
    for(auto& x: D) {
        hasAirport[x] = true;
    }

    for(auto& u: D) {
        for(auto& v: D) {
            adj[u][v] = min(adj[u][v], T);
            adj[v][u] = min(adj[v][u], T);

            dist[u][v] = min(dist[u][v], T);
            dist[v][u] = min(dist[v][u], T);
        }
    }



    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    auto get = [&]() -> ll {
        ll re = 0;
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(dist[i][j] >= BIG) continue;
                re += dist[i][j];
            }
        }
        return re;
    };



    auto ddd = [&]() -> void {
        if(isDebugging) {
            vvl dp;
            for(int i = 1; i <= n; i++) {
                vl current;
                for(int j = 1; j <= n; j++) {
                    current.emplace_back(dist[i][j]);
                }
                dp.emplace_back(current);
            }
            for(auto& x: dp) dbg(x);
        }
    };


    ll Q; cin >> Q;
    for(int _ = 0; _ < Q; _++) {
        RAYA;
        ddd();
        ll type; cin >> type;

        if(type == 1) {
            ll u, v, w; cin >> u >> v >> w;

            adj[u][v] = min(adj[u][v], w);
            adj[v][u] = min(adj[v][u], w);

            // dist[i][u] + dist[v][j]
            vl dist_from_u(n + 1, BIG);
            {
                vb vis(n + 1);
                dist_from_u[u] = 0;
                for(int _ = 0; _ < n; _++) {
                    int nxt = -1;
                    for(int j = 1; j <= n; j++) {
                        if(!vis[j] && (nxt == -1 || dist_from_u[j] < dist_from_u[nxt])) {
                            nxt = j;
                        }
                    }

                    if(dist_from_u[nxt] == BIG) {
                        break;
                    }

                    vis[nxt] = true;

                    for(int to = 1; to <= n; to++) {
                        ll len = adj[nxt][to];

                        if(dist_from_u[nxt] + len < dist_from_u[to]) {
                            dist_from_u[to] = dist_from_u[nxt] + len;
                        }
                    }
                }
            }
            vl dist_from_v(n + 1, BIG);
            {
                vb vis(n + 1);
                dist_from_v[v] = 0;
                for(int _ = 0; _ < n; _++) {
                    int nxt = -1;
                    for(int j = 1; j <= n; j++) {
                        if(!vis[j] && (nxt == -1 || dist_from_v[j] < dist_from_v[nxt])) {
                            nxt = j;
                        }
                    }

                    if(dist_from_v[nxt] == BIG) {
                        break;
                    }

                    vis[nxt] = true;

                    for(int to = 1; to <= n; to++) {
                        ll len = adj[nxt][to];

                        if(dist_from_v[nxt] + len < dist_from_v[to]) {
                            dist_from_v[to] = dist_from_v[nxt] + len;
                        }
                    }
                }
            }
            dbg(u, v, w);
            dbg(u, dist_from_u);
            dbg(v, dist_from_v);

            for(int i = 1; i <= n; i++) {
                for(int j = 1; j <= n; j++) {
                    dist[i][j] = min(dist[i][j], dist_from_u[i] + w + dist_from_v[j]);
                    dist[i][j] = min(dist[i][j], dist_from_u[j] + w + dist_from_v[i]);
                }
            }
        } else if(type == 2) {
            ll u; cin >> u;

            if(hasAirport[u]) continue;
            hasAirport[u] = true;

            for(auto& nxt: D) {
                adj[u][nxt] = min(adj[u][nxt], T);
                adj[nxt][u] = min(adj[nxt][u], T);
            }
            D.emplace_back(u);

            vl dist_from_u(n + 1, BIG);
            {
                vb vis(n + 1);
                dist_from_u[u] = 0;
                for(int _ = 0; _ < n; _++) {
                    int nxt = -1;
                    for(int j = 1; j <= n; j++) {
                        if(!vis[j] && (nxt == -1 || dist_from_u[j] < dist_from_u[nxt])) {
                            nxt = j;
                        }
                    }

                    if(dist_from_u[nxt] == BIG) {
                        break;
                    }

                    vis[nxt] = true;

                    for(int to = 1; to <= n; to++) {
                        ll len = adj[nxt][to];

                        if(dist_from_u[nxt] + len < dist_from_u[to]) {
                            dist_from_u[to] = dist_from_u[nxt] + len;
                        }
                    }
                }
            }

            for(int i = 1; i <= n; i++) {
                for(int j = 1; j <= n; j++) {
                    dist[i][j] = min(dist[i][j], dist_from_u[i] + dist_from_u[j]);
                }
            }
        } else {
            assert(type == 3);
            dbg("query", type);

            ll response = get();
            dbg(response);
            cout << response << "\n";
        }
    }
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

    int t = 1;
    //* cin >> t;
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
