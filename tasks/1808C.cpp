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

ll l, r;
vl lDigits, rDigits;
ll MAXN;

bool vis[20 + 1][10 + 1][10 + 1][2][2][2];
ll  memo[20 + 1][10 + 1][10 + 1][2][2][2];

ll dp(ll i, ll mn, ll mx, bool lst, bool lower, bool upper) {
    if(i == MAXN) {
        if(lst) return mx - mn;
        else return BIG;
    } else {
        if(vis[i][mn][mx][lst][lower][upper]) return memo[i][mn][mx][lst][lower][upper];
        vis[i][mn][mx][lst][lower][upper] = true;

        ll re = BIG;

        if(!lst) {
            re = min(re, dp(i + 1, mn, mx, lst, lower, upper));


            const int left = (MAXN - 1) - sz(to_string(l)) + 1;
            if(i <= left) {
                for(ll d = ((i == left)? lDigits[i] : 1); d <= ((i == 0)? rDigits[i] : 9); d++) {
                    re = min(re,
                        dp(i + 1, d, d, true, (i > 0) || (d < rDigits[i]), (i < left) || (d > lDigits[i]))
                    );
                }
            }
        } else {
            for(ll d = ((upper)? 0 : lDigits[i]); d <= ((lower)? 9 : rDigits[i]); d++) {
                re = min(re,
                    dp(i + 1, min(mn, d), max(mx, d), true, lower || (d < rDigits[i]), upper || (d > lDigits[i]))
                );
            }
        }

        return memo[i][mn][mx][lst][lower][upper] = re;
    }
}

string response;
void build(ll i, ll mn, ll mx, bool lst, bool lower, bool upper) {
    if(i == MAXN) {
        return;
    } else {
        ll re = dp(i, mn, mx, lst, lower, upper);

        if(!lst) {
            {
                ll nxt = dp(i + 1, mn, mx, lst, lower, upper);
                if(re == nxt) {
                    build(i + 1, mn, mx, lst, lower, upper);
                    return;
                }
            }


            const int left = (MAXN - 1) - sz(to_string(l)) + 1;
            if(i <= left) {
                for(ll d = ((i == left)? lDigits[i] : 1); d <= ((i == 0)? rDigits[i] : 9); d++) {
                    ll nxt = dp(i + 1, d, d, true, (i > 0) || (d < rDigits[i]), (i < left) || (d > lDigits[i]));
                    if(re == nxt) {
                        response.push_back(to_string(d).front());
                        build(i + 1, d, d, true, (i > 0) || (d < rDigits[i]), (i < left) || (d > lDigits[i]));
                        return;
                    }
                }
            }
        } else {
            for(ll d = ((upper)? 0 : lDigits[i]); d <= ((lower)? 9 : rDigits[i]); d++) {
                ll nxt = dp(i + 1, min(mn, d), max(mx, d), true, lower || (d < rDigits[i]), upper || (d > lDigits[i]));
                if(re == nxt) {
                    response.push_back(to_string(d).front());
                    build(i + 1, min(mn, d), max(mx, d), true, lower || (d < rDigits[i]), upper || (d > lDigits[i]));
                    return;
                }
            }
        }
    }
}

void solve() {
    auto gen = [&](vl& arr, ll x) {
        arr.clear();
        for(auto& c: to_string(x)) arr.emplace_back(ll(c - '0'));
        reverse(all(arr));
        while(sz(arr) < MAXN) arr.emplace_back(0LL);
        reverse(all(arr));
    };

    cin >> l >> r;
    MAXN = max(ll(sz(to_string(l))), ll(sz(to_string(r))));

    gen(lDigits, l);
    gen(rDigits, r);
    dbg(l, r);
    dbg(MAXN);
    dbg(lDigits, rDigits);


    memset(vis, false, sizeof(vis));
    ll re = dp(0, 10, 10, false, false, false);
    dbg(re);
    response.clear();
    build(0, 10, 10, false, false, false);
    dbg(response);
    cout << response << "\n";
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
