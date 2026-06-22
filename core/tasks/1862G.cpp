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

tcT > void remDup(vector<T> &v) {  // sort and remove duplicates
	sort(all(v));
	v.erase(unique(all(v)), end(v));
}

ll brute(ll n, vl a) {
    while(true) {
        remDup(a);
        if(sz(a) == 1) break;
        vl b = a;

        vl p(sz(b)); iota(all(p), 1);
        reverse(all(p));

        for(int i = 0; i < sz(b); i++) {
            b[i] += p[i];
        }

        a = b;
    }

    return a.ft;
}

ll slv(ll n, vl a) {
    sort(a.begin(), a.end());
    ll mxdiff = 0;
    for(int i = 0; i + 1 < sz(a); i++) {
        mxdiff = max(mxdiff, a[i + 1] - a[i]);
    }
    return a.bk + mxdiff;
}

using Query = pl;
void solve() {
    //* <>
    ll n; cin >> n;
    vl a(n); for(auto& x: a) cin >> x;

    ll q; cin >> q;
    V<Query> queries(q); for(auto& [i, x]: queries) {
        cin >> i >> x;
        i--;
    }
    dbg(n);
    dbg(a);
    dbg(q);
    dbg(queries);

    vl b = a; sort(b.begin(), b.end());

    multiset<ll> ms; for(auto& x: b) ms.emplace(x);
    map<ll, ll> hist; for(auto& x: b) hist[x]++;

    multiset<ll> diffs; diffs.emplace(0);
    for(int i = 0; i + 1 < n; i++) diffs.emplace(b[i + 1] - b[i]);


    auto upd = [&](ll i, ll x) -> void {
        dbg(i, a[i], x, ms, diffs);
        dbg(a);
        dbg("Should remove", a[i]);
        {
            auto it_left = ms.lower_bound(a[i]);
            if(hist[a[i]] == 1 && it_left != ms.begin()) {
                it_left--;
                dbg(*it_left, a[i] - (*it_left));
                diffs.erase(diffs.find(a[i] - (*it_left)));
            }
        }
        {
            auto it_right = ms.upper_bound(a[i]);
            if(hist[a[i]] == 1 && it_right != ms.end()) {
                dbg(*it_right, (*it_right) - a[i]);
                diffs.erase(diffs.find((*it_right) - a[i]));
            }
        }
        {
            auto it_left = ms.lower_bound(a[i]);
            auto it_right = ms.upper_bound(a[i]);
            if(hist[a[i]] == 1 && it_left != ms.begin() && it_right != ms.end()) {
                it_left--;
                dbg("add", (*it_right) - (*it_left));
                diffs.emplace((*it_right) - (*it_left));
            }
        }
        ms.erase(ms.find(a[i]));
        hist[a[i]]--;


        dbg(ms, diffs);

        ms.emplace(x);
        a[i] = x;
        hist[a[i]]++;
        dbg("Should add", x);

        {
            auto it_left = ms.lower_bound(x);
            auto it_right = ms.upper_bound(x);
            if(hist[a[i]] == 1 && it_left != ms.begin() && it_right != ms.end()) {
                it_left--;
                dbg("rem", (*it_right) - (*it_left));
                diffs.erase(diffs.find((*it_right) - (*it_left)));
            }
        }

        {
            auto it_left = ms.lower_bound(a[i]);
            if(hist[a[i]] == 1 && it_left != ms.begin()) {
                it_left--;
                dbg("add", a[i] - (*it_left));
                diffs.emplace(a[i] - (*it_left));
            }
        }
        {
            auto it_right = ms.upper_bound(a[i]);
            if(hist[a[i]] == 1 && it_right != ms.end()) {
                dbg("add", (*it_right) - a[i]);
                diffs.emplace((*it_right) - a[i]);
            }
        }

        dbg(ms, diffs);
    };

    auto query = [&]() -> ll {
        dbg("======================");
        dbg("qry");
        assert(!ms.empty());
        assert(!diffs.empty());
        ll res = (*ms.rbegin()) + (*diffs.rbegin());
        dbg(*ms.rbegin(), *diffs.rbegin(), res);
        return res;
    };

    vl response;
    for(auto& [i, x]: queries) {
        RAYA;
        upd(i, x);
        response.emplace_back(query());
    }
    dbg(response);
    for(auto& x: response) cout << x << " ";
    cout << "\n";
}

ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }
int main() {
    cin.tie(0)->sync_with_stdio(0);

    //* <>

    while(0) {
        RAYA;
        ll n = rng_ll(1, 100);
        vl a(n); for(auto& x: a) x = rng_ll(1, 12);
        dbg(n);
        dbg(a);

        ll ans = brute(n, a);
        ll greedy = slv(n, a);
        dbg(ans, greedy);
        assert(ans == greedy);
    }

    int t = 1; cin >> t;
    while(t--) {
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
