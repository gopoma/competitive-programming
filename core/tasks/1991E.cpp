//* sometimes pragmas don't work, if so, just comment it!
//? #pragma GCC optimize ("Ofast")
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
const int INF = int(1e9) + 5;
const ll BIG = ll(1e18) + 5;
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

void solve() {
    ll n, m; cin >> n >> m;

    vector<vector<ll>> adj(n + 1);
    for(int i = 0; i < m; i++) {
        ll u, v; cin >> u >> v;

        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    set<ll> reds, blues;
    {
        const ll RED = 1;
        const ll BLUE = 2;

        vector<bool> vis(n + 1);
        vector<ll> color(n + 1);
        deque<ll> q;

        vis[1] = true;
        color[1] = RED;
        q.emplace_back(1);

        bool ok = true;
        while(!q.empty()) {
            auto cur = q.front(); q.pop_front();

            for(auto& nxt: adj[cur]) {
                if(vis[nxt]) {
                    ok &= (color[cur] != color[nxt]);
                } else {
                    vis[nxt] = true;
                    color[nxt] = (color[cur] == RED)? BLUE : RED;
                    q.emplace_back(nxt);
                }
            }
        }

        if(!ok) {
            cout << "Alice" << endl;

            for(int i = 0; i < n; i++) {
                cout << "1 2" << endl;
                ll id, c; cin >> id >> c;
            }

            return;
        }

        for(int u = 1; u <= n; u++) {
            if(color[u] == RED) reds.emplace(u);
            else blues.emplace(u);
        }
    }

    cout << "Bob" <<  endl;

    map<char, ll> C;
    {
        ll red, blue; cin >> red >> blue;
        C['R'] = red;
        C['A'] = blue;
        C['B'] = 6 - red - blue;

        assert(!reds.empty());



        ll id = *reds.begin(); reds.erase(reds.find(id));
        assert(1 <= id && id <= n);
        cout << id << " " << C['R'] << endl;
    }

    while(!reds.empty() && !blues.empty()) {
        ll a, b; cin >> a >> b;

        if(a == C['R'] || b == C['R']) {
            ll id = *reds.begin(); reds.erase(reds.find(id));
            assert(1 <= id && id <= n);
            cout << id << " " << C['R'] << endl;
        } else if(a == C['A'] || b == C['A']) {
            ll id = *blues.begin(); blues.erase(blues.find(id));
            assert(1 <= id && id <= n);
            cout << id << " " << C['A'] << endl;
        } else assert(false);
    }

    for(auto& id: reds) {
        ll a, b; cin >> a >> b;
        if(a == C['R'] || b == C['R']) {
            cout << id << " " << C['R'] << endl;
        } else {
            cout << id << " " << C['B'] << endl;
        }
    }
    for(auto& id: blues) {
        ll a, b; cin >> a >> b;
        if(a == C['A'] || b == C['A']) {
            cout << id << " " << C['A'] << endl;
        } else {
            cout << id << " " << C['B'] << endl;
        }
    }
}

ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }

// shuffle a vector
template<class T> void shuf(vector<T>& v) { shuffle(all(v),rng); }

int main() {
    cin.tie(0)->sync_with_stdio(0);

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
