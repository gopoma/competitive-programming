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

using Query = tuple<ll, ll, ll, ll>;
void solve() {
    ll n, q; cin >> n >> q;
    vector<char> S(n + 5);
    for(int i = 1; i <= n; i++) cin >> S[i];
    vector<Query> que(q);
    for(auto& [x, y, L, R]: que) {
        cin >> x >> y >> L >> R;
    }



    map<char, pair<ll, ll>> D;
    D['U'] = {0, +1};
    D['D'] = {0, -1};
    D['L'] = {-1, 0};
    D['R'] = {+1, 0};



    vector<pair<ll, ll>> pref(n + 5);
    {
        pref[0] = {0, 0};
        for(int i = 1; i <= n; i++) {
            pref[i].first  = pref[i - 1].first  + D[S[i]].first;
            pref[i].second = pref[i - 1].second + D[S[i]].second;
        }
    }
    map<pair<ll, ll>, vector<ll>> PREF;
    for(int i = 0; i <= n; i++) {
        PREF[pref[i]].emplace_back(i);
    }



    vector<pair<ll, ll>> suff(n + 5);
    {
        suff[n + 1] = {0, 0};
        for(int i = n; i >= 1; i--) {
            suff[i].first  = suff[i + 1].first + D[S[i]].first;
            suff[i].second = suff[i + 1].second + D[S[i]].second;
        }
    }
    dbg(suff);
    map<pair<ll, ll>, vector<ll>> SUFF;
    for(int i = 1; i <= n; i++) {
        SUFF[suff[i]].emplace_back(i);
    }



    for(auto& [_, v]: PREF) sort(v.begin(), v.end());
    for(auto& [_, v]: SUFF) sort(v.begin(), v.end());



    auto check = [&](map<pair<ll, ll>, vector<ll>>& G, ll left, ll right, pair<ll, ll> tar) -> bool {
        auto itL = lower_bound(all(G[tar]), left);
        if(itL == G[tar].end()) return false;

        auto itR = upper_bound(all(G[tar]), right);
        if(itR == G[tar].begin()) return false;
        itR--;

        ll l = *itL;
        ll r = *itR;

        return (left <= l && r <= right && l <= r);
    };

    for(auto& [x, y, L, R]: que) {
        dbg("query", x, y, L, R);

        bool ok = false;
        if(0 <= (L - 1)) ok |= check(PREF, 0, L - 1, make_pair(x, y));

        {
            ll tx = x + suff[R + 1].first  - pref[L - 1].first;
            ll ty = y + suff[R + 1].second - pref[L - 1].second;
            dbg(tx, ty);

            ok |= check(SUFF, L, R, make_pair(tx, ty));
        }

        if(R + 1 <= n)   ok |= check(PREF, R + 1, n, make_pair(x, y));

        cout << (ok?"YES":"NO") << "\n";
    }
}

ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }

// shuffle a vector
template<class T> void shuf(vector<T>& v) { shuffle(all(v),rng); }

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t = 1;
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
