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
using pl = pair<ll, ll>;

#define tcT template<class T
tcT> using V = vector<T>;
using vl = V<ll>;

#define sz(x) int((x).size())
#define all(x) bg(x), end(x)

void setIn(string s) { freopen(s.c_str(), "r", stdin); }

void solve() {
    ll n, m; cin >> n >> m;
    V<pl> edges(m);
    for(auto& [u, v]: edges) cin >> u >> v;

    V<vl> G(n + 1);
    for(auto& [u, v]: edges) {
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }

    vl res(n + 1);
    V<bool> vis(n + 1);

    deque<ll> L; //* lower
    L.emplace_back(1);
    set<ll> R; //* greater

    ll cnt = 0;
    deque<ll> q;
    for(ll x = 1; x <= n; x++) {
        vl todo;
        for(auto& it: R) {
            if(it > x) break;
            L.emplace_back(it);
            todo.emplace_back(it);
        }
        for(auto& it: todo) {
            R.erase(R.find(it));
        }

        while(!L.empty()) {
            auto cur = L.front(); L.pop_front();
            if(!vis[cur]) {
                vis[cur] = true;
                cnt++;
            }
            for(auto& nxt: G[cur]) {
                if(nxt <= x) {
                    if(vis[nxt]) continue;
                    else {
                        vis[nxt] = true;
                        cnt++;
                        L.emplace_back(nxt);
                    }
                } else {
                    R.emplace(nxt);
                }
            }
        }

        if(cnt < x) res[x] = -1;
        else res[x] = sz(R);
    }

    for(ll x = 1; x <= n; x++) {
        cout << res[x] << "\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t = 1; //* cin >> t;
    while(t--) {
        solve();
        RAYA;
    }
}
