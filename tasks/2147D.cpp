#pragma GCC optimize ("Ofast")

#undef _GLIBCXX_DEBUG

#include <bits/stdc++.h>
using namespace std;



// Debugger
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
// /Debugger




using ll = long long;
using db = long double;
using str = string;

using pi = pair<int, int>;
using pl = pair<ll, ll>;

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
#define pb push_back
#define eb emplace_back

#define FOR(i, a, b) for(int i = (a); i < (b); ++i)
#define F0R(i, a)    FOR(i, 0, a)
#define ROF(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define R0F(i, a)    ROF(i, 0, a)
#define rep(a) F0R(_, a)

const int MOD = int(1e9) + 7;
const int INF = int(1e9) + 5;
const ll BIG = ll(1e18) + 5;
const db PI = acos((db)-1);
mt19937 rng(0);

void setIn(string S) {
    freopen(S.c_str(), "r", stdin);
}

ll rng_ll(ll L, ll R) {
    assert(L <= R);
    return uniform_int_distribution<ll>(L, R)(rng);
}

// Template
// /Template

ll brute(ll n, const vl a) {
    map<vl, map<bool, bool>> vis;
    map<vl, map<bool, ll>> memo;
    auto dp = [&](auto&& dp, vl aCurrent, bool AliceTurn) -> ll {
        map<ll, ll> hist;
        for(auto& x: aCurrent) hist[x]++;

        if(hist[0] == n) {
            return 0;
        }

        if(vis[aCurrent][AliceTurn]) return memo[aCurrent][AliceTurn];
        vis[aCurrent][AliceTurn] = true;

        if(AliceTurn) {
            ll re = 0;

            for(auto& [x, cnt]: hist) {
                if(x == 0) continue;

                vl nxtACurrent = aCurrent;
                for(auto& it: nxtACurrent) {
                    if(it == x) {
                        it--;
                    }
                }

                re = max(re, cnt + dp(dp, nxtACurrent, !AliceTurn));
            }

            return memo[aCurrent][AliceTurn] = re;
        } else {
            ll re = BIG;

            for(auto& [x, cnt]: hist) {
                if(x == 0) continue;

                vl nxtACurrent = aCurrent;
                for(auto& it: nxtACurrent) {
                    if(it == x) {
                        it--;
                    }
                }

                re = min(re, dp(dp, nxtACurrent, !AliceTurn));
            }

            return memo[aCurrent][AliceTurn] = re;
        }
    };

    return dp(dp, a, true);
}

ll slv(ll n, vl a) {
    ll re = -BIG;
    for(ll k = 0; k < 1; k++) {
        map<ll, ll> hist;
        for(auto& x: a) hist[x]++;

        ll sum = accumulate(all(a), 0LL);
        ll Alice = 0;

        bool par = bool(k);
        bool first = true;
        for(auto& [val, cnt]: hist) {
            ll up = (val + 1LL) / 2LL;
            ll down = val - up;


            if(par) {
                Alice += cnt * up;
            } else {
                Alice += cnt * down;
            }
            if(first) {

            }

            if(up != down) {
                par = !par;
            }
        }
        re = max(re, max(Alice, sum - Alice));
    }
    return re;
}

void solve() {
    ll n; cin >> n;
    vl a(n); for(auto& x: a) cin >> x;
    dbg(n);
    dbg(a);

    ll sum = accumulate(all(a), 0LL);
    ll Alice = slv(n, a);
    ll Bob = sum - Alice;
    dbg(sum, Alice, Bob);
    cout << Alice << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    while(1) {
        RAYA;
        RAYA;
        RAYA;

        ll n = rng_ll(3, 6);
        vl a(n); for(auto& x: a) x = rng_ll(1, 6);
        dbg(n);
        dbg(a);

        set<ll> aux;
        for(auto& x: a) aux.emplace(x);

        ll ans = brute(n, a);
        ll gre = slv(n, a);
        ll sum = accumulate(all(a), 0LL);
        dbg(sum, ans, sum - ans);
        dbg(ans, gre);
        assert(ans == gre);


        // ll Alice = ans;
        // ll Bob = sum - Alice;
        // assert(abs(Alice - Bob) <= 1);
    }

    int t = 1;
    cin >> t;

    while(t--) {
        RAYA;
        RAYA;
        RAYA;
        RAYA;
        solve();
    }

    return 0;
}

