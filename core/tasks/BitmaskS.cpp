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

ll rangeXOR(ll n) {
    if(n < 0) return 0;

    if (n % 4 == 0)
        return n;

    if (n % 4 == 1)
        return 1;

    if (n % 4 == 2)
        return n + 1LL;

    return 0;
}

ll rangeXOR(ll l, ll r) {
    return rangeXOR(r) ^ rangeXOR(l - 1);
}

ll brute(ll n, vl a) {
    auto q = [&](ll i) -> ll {
        ll res = a[i - 1];
        for(ll mod = 1; mod <= n; mod++) {
            res ^= (i % mod);
        }
        return res;
    };
    ll Q = 0;
    for(ll i = 1; i <= n; i++) Q ^= q(i);
    return Q;
}

ll slv(ll n, vl a) {
    ll res = 0;
    for(auto& x: a) {
        res ^= x;
    }

    for(ll mod = 1; mod <= n; mod++) {
        ll blockSize = mod;
        ll blocks = (n + 1) / blockSize;
        ll blockXOR = rangeXOR(0, mod - 1);

        if(blocks & 1) res ^= blockXOR;
        ll queda = (n + 1) - blocks * blockSize;
        if(queda == 0) continue;
        res ^= rangeXOR(0, queda - 1LL);
    }

    return res;
}

void solve() {
    ll n; cin >> n;
    vl a(n);
    for(auto& x: a) {
        cin >> x;
    }
    ll res = slv(n, a);
    cout << res << "\n";
}

ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }

int main() {
    cin.tie(0)->sync_with_stdio(0);

    while(0) {
        ll n = rng_ll(1, 10);
        vl a(n); for(auto& x: a) x = rng_ll(0, ll(1e9));
        ll ans = brute(n, a);
        ll greedy = slv(n, a);
        dbg(ans, greedy);
        assert(ans == greedy);
    }

    solve();
}
