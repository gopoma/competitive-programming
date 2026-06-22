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

ll calc(vl p) {
    ll n = sz(p);
    ll re = 0;
    for(int i = 0; i < n; i++) {
        ll u = i;
        ll v = (i + 1) % n;
        re += abs(p[u] - p[v]);
    }
    return re;
}

ll brute(ll n, vl a, vl b) {
    map<ll, ll> where_a, where_b;
    for(int i = 0; i < n; i++) {
        where_a[a[i]] = i;
        where_b[b[i]] = i;
    }

    auto work = [&](vl p) -> ll {
        vl c(n), d(n);
        for(int i = 0; i < n; i++) {
            c[where_a[a[i]]] = p[i];
            d[where_b[a[i]]] = p[i];
        }
        ll re = 0;
        for(int i = 0; i < n; i++) {
            re += abs(c[i] - d[i]);
        }
        return re;
    };

    ll re = 0;
    vl p(n); iota(all(p), 1LL);
    do {
        re = max(re, work(p));
    } while(next_permutation(all(p)));
    return re;
}

vl build(ll n, set<ll>& aux) {
    vl re(n);
    for(int i = 0; i < n; i++) {
        if(i % 2 == 0) {
            ll mn = *aux.begin();
            aux.erase(mn);
            re[i] = mn;
        } else {
            ll mx = *aux.rbegin();
            aux.erase(mx);
            re[i] = mx;
        }
    }
    return re;
}

ll slv(ll n, vl a, vl b) {
    set<ll> aux;
    for(ll x = 1; x <= n; x++) {
        aux.emplace(x);
    }

    map<ll, ll> where_a, where_b;
    for(int i = 0; i < n; i++) {
        where_a[a[i]] = i;
        where_b[b[i]] = i;
    }
    map<ll, bool> vis;

    V<vl> odd, even;
    for(int i = 0; i < n; i++) {
        if(!vis[where_a[a[i]]]) {
            ll cur = where_a[a[i]];
            vl komp;
            while(!vis[cur]) {
                vis[cur] = true;
                komp.emplace_back(cur);
                cur = where_a[b[cur]];
            }
            if(sz(komp) % 2 == 0) {
                even.emplace_back(komp);
            } else {
                odd.emplace_back(komp);
            }
        }
    }

    sort(all(odd), [&](vl& A, vl& B) {
        return sz(A) > sz(B);
    });
    sort(all(even), [&](vl& A, vl& B) {
        return sz(A) > sz(B);
    });
    dbg(odd);
    dbg(even);

    map<ll, ll> forwards;
    for(auto& komp: even) {
        vl p = build(sz(komp), aux);
        for(int i = 0; i < sz(komp); i++) {
            forwards[komp[i]] = p[i];
        }
    }
    for(auto& komp: odd) {
        vl p = build(sz(komp) - 1, aux);
        for(int i = 0; i < sz(komp) - 1; i++) {
            forwards[komp[i]] = p[i];
        }
    }
    for(auto& komp: odd) {
        for(int i = sz(komp) - 1; i < sz(komp); i++) {
            forwards[komp[i]] = *aux.begin();
            aux.erase(*aux.begin());
        }
    }

    vl c(n), d(n);
    for(int i = 0; i < n; i++) {
        c[where_a[a[i]]] = forwards[i];
        d[where_b[a[i]]] = forwards[i];
    }
    ll re = 0;
    for(int i = 0; i < n; i++) {
        re += abs(c[i] - d[i]);
    }
    return re;
}

void solve() {
    ll n; cin >> n;
    vl a(n), b(n);
    for(auto& x: a) cin >> x;
    for(auto& x: b) cin >> x;
    dbg(n);
    dbg(a);
    dbg(b);
    ll re = slv(n, a, b);
    dbg(re);
    cout << re << "\n";
}

ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }

// shuffle a vector
template<class T> void shuf(vector<T>& v) { shuffle(all(v),rng); }

int main() {
    cin.tie(0)->sync_with_stdio(0);

    // const int n = 5;
    // vl p(n); iota(all(p), 0LL);
    // ll re = 0;
    // do {
    //     re = max(re, calc(p));
    // } while(next_permutation(all(p)));
    // dbg(re);

    // vl a = build(n);
    // dbg(a, calc(a), re);
    // assert(re == calc(a));

    while(0) {
        RAYA;
        RAYA;
        RAYA;
        ll n = rng_ll(1, 10);
        vl a(n), b(n);
        iota(all(a), 1LL); shuf(a);
        iota(all(b), 1LL); shuf(b);
        dbg(n);
        dbg(a);
        dbg(b);
        ll ans = brute(n, a, b);
        ll gre = slv(n, a, b);
        dbg(ans, gre);
        assert(ans == gre);
    }

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
