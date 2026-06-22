//* sometimes pragmas don't work, if so, just comment it!
#pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

//! #undef _GLIBCXX_DEBUG //? for Stress Testing

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
#define MACRO(code) do {code} while (false)
#define dbg(x)      {auto xd = x; cout << "Line(" << __LINE__ << "): " << "\033[1;34m" << #x << "\033[0;32m = \033[35m" << to_string(xd) << "\033[0m" << endl;}
#define dbg(...)    MACRO(cout << "Line(" << __LINE__ << "): " << "\033[1;34m" << "[" << #__VA_ARGS__ << "]\033[35m:"; debug_out(__VA_ARGS__); cout << "\033[0m";)

#define GA          dbg(0)
#define RAYA        cout << "\033[101m" << "================================" << "\033[0m" << endl;
#else
#define dbg(x)
#define dbg(...)
#define GA
#define RAYA
#endif
//* /Debugger

using ll = long long;
using db = long double; // or double if tight TL
using str = string;

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

#define sz(x) int((x).size())
#define all(x) begin(x), end(x)
#define sor(x) sort(all(x))
#define rsz resize
#define pb push_back
#define ft front()
#define bk back()

#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define rep(a) F0R(_,a)
#define each(a,x) for (auto& a: x)

const int MOD = 1e9+7;
const db PI = acos((db)-1);
mt19937 rng(0); // or mt19937_64
//* mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

tcT> bool ckmin(T& a, const T& b) {
	return b < a ? a = b, 1 : 0; } // set a = min(a,b)
tcT> bool ckmax(T& a, const T& b) {
	return a < b ? a = b, 1 : 0; } // set a = max(a,b)

void setIn(string s) { freopen(s.c_str(), "r", stdin); }

const auto beg_time = std::chrono::high_resolution_clock::now();
// https://stackoverflow.com/questions/47980498/accurate-c-c-clock-on-a-multi-core-processor-with-auto-overclock?noredirect=1&lq=1
double time_elapsed() {
	return chrono::duration<double>(std::chrono::high_resolution_clock::now() -
	                                beg_time)
	    .count();
}

//* Template
//* /Template

//* int dp[1000 + 1][(1 << 15) + 1];
bool vis[120 + 1][(1 << 15) + 1];
int memo[120 + 1][(1 << 15) + 1];
int adj[15 + 1][15 + 1];
const int INF = int(1e9);

void solve() {
    int n, m; cin >> n >> m;

    for(int u = 0; u < n; u++) {
        for(int v = 0; v < n; v++) {
            adj[u][v] = INF;
        }
    }

    using Edge = tuple<int, int, int>;
    vector<Edge> edges(m);

    int initial_mask = 0;
    int sum = 0;
    for(auto& [u, v, d]: edges) {
        cin >> u >> v >> d;
        adj[u][v] = min(adj[u][v], d);
        adj[v][u] = adj[u][v];
        initial_mask ^= (1 << u);
        initial_mask ^= (1 << v);
        sum += d;
    }

    vector<Edge> new_edges;
    for(int u = 0; u < n; u++) {
        for(int v = u + 1; v < n; v++) {
            if(adj[u][v] < INF) {
                new_edges.emplace_back(u, v, adj[u][v]);
            }
        }
    }
    swap(edges, new_edges);
    m = sz(edges);

//*    for(int i = m; i >= 0; i--) {
//*        for(int mask = 0; mask < (1 << n); mask++) {
//*            if(i == m) {
//*                if(mask == 0) dp[i][mask] = sum;
//*                else dp[i][mask] = INF;
//*            } else {
//*                dp[i][mask] = INF;
//*                dp[i][mask] = min(dp[i][mask], dp[i + 1][mask]);
//*                auto [u, v, d] = edges[i];
//*                dp[i][mask] = min(dp[i][mask], dp[i + 1][mask ^ (1 << u) ^ (1 << v)] + d);
//*            }
//*        }
//*    }
//*    int response = dp[0][initial_mask];
//*    cout << response << "\n";

    auto dp = [&](auto&& dp, int i, int mask) {
        if(i == m) {
            if(mask == 0) return sum;
            else return INF;
        }

        if(vis[i][mask]) return memo[i][mask];
        vis[i][mask] = true;

        // no take
        int res = dp(dp, i + 1, mask);

        // take
        auto [u, v, d] = edges[i];
        res = min(res, dp(dp, i + 1, mask ^ (1 << u) ^ (1 << v)) + d);

        return memo[i][mask] = res;
    };

    int res = dp(dp, 0, initial_mask);
    cout << res << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t = 1; //* cin >> t;
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
