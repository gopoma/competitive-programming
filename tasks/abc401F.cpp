#pragma GCC optimize ("trapv")

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

const ll BIG = ll(1e18);
void solve() {
    V<vl> E;
    for(int _ = 0; _ < 2; _++) {
        ll n; cin >> n;
        V<pl> edges(n - 1);
        for(auto& [u, v]: edges) {
            cin >> u >> v;
            u--; v--;
        }

        V<vl> adj(n);
        for(auto& [u, v]: edges) {
            adj[u].emplace_back(v);
            adj[v].emplace_back(u);
        }

        ll A = -1;
        {
            deque<ll> q; q.emplace_back(0);
            V<bool> vis(n); vis[0] = true;
            vl dist(n); dist[0] = 0;
            while(!q.empty()) {
                auto cur = q.front(); q.pop_front();
                for(auto& nxt: adj[cur])  {
                    if(!vis[nxt]) {
                        vis[nxt] = true;
                        dist[nxt] = dist[cur] + 1;
                        q.emplace_back(nxt);
                    }
                }
            }
            pl res = make_pair(-BIG, -BIG);
            for(ll u = 0; u < n; u++) {
                ckmax(res, make_pair(dist[u], u));
            }
            A = res.second;
        }

        vl dist_from_A;
        ll B = -1;
        {
            deque<ll> q; q.emplace_back(A);
            V<bool> vis(n); vis[A] = true;
            vl dist(n); dist[A] = 0;
            while(!q.empty()) {
                auto cur = q.front(); q.pop_front();
                for(auto& nxt: adj[cur])  {
                    if(!vis[nxt]) {
                        vis[nxt] = true;
                        dist[nxt] = dist[cur] + 1;
                        q.emplace_back(nxt);
                    }
                }
            }
            pl res = make_pair(-BIG, -BIG);
            for(ll u = 0; u < n; u++) {
                ckmax(res, make_pair(dist[u], u));
            }
            B = res.second;
            dist_from_A = dist;
        }

        vl dist_from_B;
        {
            deque<ll> q; q.emplace_back(B);
            V<bool> vis(n); vis[B] = true;
            vl dist(n); dist[B] = 0;
            while(!q.empty()) {
                auto cur = q.front(); q.pop_front();
                for(auto& nxt: adj[cur])  {
                    if(!vis[nxt]) {
                        vis[nxt] = true;
                        dist[nxt] = dist[cur] + 1;
                        q.emplace_back(nxt);
                    }
                }
            }
            dist_from_B = dist;
        }

        assert(A != -1 && B != -1);

        vl xd(n);
        for(int u = 0; u < n; u++) {
            xd[u] = max(dist_from_A[u], dist_from_B[u]);
        }
        E.emplace_back(xd);
    }

    dbg(E);
    vl X = E.ft; sort(X.begin(), X.end());
    vl Y = E.bk; sort(Y.begin(), Y.end());
    vl pref_Y = Y;
    for(int i = 1; i < sz(pref_Y); i++) pref_Y[i] += pref_Y[i - 1];
    auto query = [&](ll L, ll R) -> ll {
        if(L < 0 || R < 0 || L >= sz(pref_Y) || R >= sz(pref_Y) || L > R) return 0;
        ll S = pref_Y[R];;
        if(0 <= L - 1) S -= pref_Y[L - 1];
        return S;
    };
    ll d = *max_element(X.begin(), X.end());
    ll d2 = *max_element(Y.begin(), Y.end());
    ll dmax = max(d, d2);
    ll res = 0;
    for(int i = 0; i < sz(X); i++) {
        //* X[i] + 1 + y > dmax
        //* y > dmax - X[i] - 1
        // 0 - sz(X)
        ll j = upper_bound(Y.begin(), Y.end(), dmax - X[i] - 1) - Y.begin();
        ll contrib = 0;
        if(0 <= j - 1) contrib += j * dmax;
        if(j < sz(Y)) {
            ll siz = (sz(Y) - 1) - j + 1;
            contrib += siz * (X[i] + 1) + query(j, sz(Y) - 1);
        }
        dbg(i, X[i], j, contrib);
        res += contrib;
    }
    cout << res << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    solve();
}
