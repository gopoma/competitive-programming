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
#define dbg(...)    MACRO(cout << "Line(" << __LINE__ << "): " << "\033[1;34m" << "[" << #__VA_ARGS__ << "]\033[35m:"; debug_out(__VA_ARGS__); cout << "\033[0m" << endl;)

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

ll n, d;
ll N;
ll val[ll(2e5) + 5];
ll cnt[ll(2e5) + 5];
bool already[ll(2e5) + 5];
ll memo[ll(2e5) + 5];

const ll BIG = ll(1e18) + 5;
ll dp(ll i) {
    if(i >= N - 1) return 0;

    if(already[i]) return memo[i];
    already[i] = true;

    ll res = BIG;
    //* until i is good
    //* mark i
    res = min(res, dp(i + 1) + cnt[i]);
    //* mark i + 1
    res = min(res, dp(i + 2) + cnt[i + 1]);
    return memo[i] = res;
}

void solve() {
    cin >> n >> d;

    vl a(n); for(auto& x: a) cin >> x;
    sort(a.begin(), a.end());
    set<ll> b; for(auto& x: a) b.emplace(x);

    if(d == 0) {
        ll res = sz(a) - sz(b);
        cout << res << "\n";
        return;
    }

    map<ll, ll> hist; for(auto& x: a) hist[x]++;
    map<ll, bool> vis;
    vector<vector<ll>> G;
    for(auto& x: b) {
        if(vis[x]) continue;

        vector<ll> C;
        ll cur = x;
        while(!vis[cur] && b.count(cur)) {
            vis[cur] = true;
            C.emplace_back(cur);
            cur += d;
        }
        G.emplace_back(C);
    }

    ll res = 0;
    for(auto& vec: G) {
        dbg(vec);
        N = sz(vec);
        for(int i = 0; i < N; i++) {
            val[i] = vec[i];
            cnt[i] = hist[vec[i]];
            already[i] = false;
        }
        for(int i = 0; i < N; i++) {
            dbg(i, val[i], cnt[i]);
        }

        res += dp(0);
    }

    cout << res << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    solve();
}
