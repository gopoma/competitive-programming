#pragma GCC optimize ("Ofast")

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

ll dx[4]{-1, +1,  0,  0};
ll dy[4]{ 0,  0, -1, +1};
void solve() {
    int n, m; cin >> n >> m;
    V<string> S(n);
    for(auto& x: S) cin >> x;
    int sx, sy; cin >> sx >> sy; sx--; sy--;
    int gx, gy; cin >> gx >> gy; gx--; gy--;

    dbg(n, m, sx, sy, gx, gy);
    for(auto& it: S) dbg(it);

    auto check = [&](int x, int y) -> bool {
        bool ok = (0 <= x && x < n);
        bool ok2 = (0 <= y && y < m);
        return (ok && ok2);
    };

    using Info = tuple<int, int, int>;
    multiset<Info> ms; ms.emplace(0, sx, sy);

    V<V<bool>> vis(n, V<bool>(m));
    V<vl> dist(n, vl(m));
    while(!ms.empty()) {
        auto it = *ms.begin();
        auto [d, cx, cy] = it; ms.erase(ms.find(it));

        if(vis[cx][cy]) continue;
        vis[cx][cy] = true;
        dist[cx][cy] = d;

        for(int k = 0; k < 4; k++) {
            {
                ll nx = cx + dx[k];
                ll ny = cy + dy[k];
                if(check(nx, ny) && S[nx][ny] == '.') {
                    ms.emplace(d, nx, ny);
                } else if(check(nx, ny) && S[nx][ny] == '#') {
                    ms.emplace(d + 1, nx, ny);
                }
            }
            {
                ll nx = cx + dx[k] + dx[k];
                ll ny = cy + dy[k] + dy[k];
                if(check(nx, ny)) {
                    ms.emplace(d + 1, nx, ny);
                }
            }
        }
    }
    cout << dist[gx][gy] << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    solve();
}
