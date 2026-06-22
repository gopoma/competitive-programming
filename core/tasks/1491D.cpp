//* sometimes pragmas don't work, if so, just comment it!
#pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

//! #undef _GLIBCXX_DEBUG //? for Stress Testing

#include <bits/stdc++.h>
using namespace std;



#ifdef LOCAL
    #include "debug.h"
#else
    #define dbg(...)     0
    #define chk(...)     0

    #define RAYA         0
#endif



const auto beg_time = std::chrono::high_resolution_clock::now();
double time_elapsed() { return chrono::duration<double>(std::chrono::high_resolution_clock::now() - beg_time) .count(); }



// building blocks
using ll  = long long;
using db  = long double;
using str = string;

//? priority_queue for minimum
template<class T> using pqg = priority_queue<T, vector<T>, greater<T>>;

using ull  = unsigned long long;
//? using i64  = long long;
//? using u64  = uint64_t;
//? using i128 = __int128;
//? using u128 = __uint128_t;
//? using f128 = __float128;



// pairs
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<db, db>;

#define mp make_pair
#define f  first
#define s  second



#define tcT template <class T
#define tcTU tcT, class U

tcT > using V = vector<T>;
tcT, size_t SZ > using AR = array<T, SZ>;
using vi = V<int>;
using vb = V<bool>;
using vl = V<ll>;
using vd = V<db>;
using vs = V<str>;
using vpi = V<pi>;
using vpl = V<pl>;
using vpd = V<pd>;

using vvi = V<vi>;
using vvl = V<vl>;
using vvb = V<vb>;



// vectors
// oops size(x), rbegin(x), rend(x) need C++17
#define sz(x) int((x).size())
#define bg(x) begin(x)
#define all(x) bg(x), end(x)
#define rall(x) x.rbegin(), x.rend()
#define sor(x) sort(all(x))
#define rsz resize
#define ins insert
#define pb push_back
#define eb emplace_back
#define ft front()
#define bk back()
#define ts to_string

#define lb lower_bound
#define ub upper_bound



// loops
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define F0R(i, a) FOR(i, 0, a)
#define ROF(i, a, b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i, a) ROF(i, 0, a)
#define rep(a) F0R(_, a)
#define each(a, x) for (auto &a : x)



ll cdiv(ll a, ll b) {
	return a / b + ((a ^ b) > 0 && a % b);
}  // divide a by b rounded up
ll fdiv(ll a, ll b) {
	return a / b - ((a ^ b) < 0 && a % b);
}  // divide a by b rounded down

tcT > bool ckmin(T &a, const T &b) {
	return b < a ? a = b, 1 : 0;
}  // set a = min(a,b)
tcT > bool ckmax(T &a, const T &b) {
	return a < b ? a = b, 1 : 0;
}  // set a = max(a,b)

tcT > void remDup(vector<T> &v) {  // sort and remove duplicates
	sort(all(v));
	v.erase(unique(all(v)), end(v));
}
tcTU > void safeErase(T &t, const U &u) {
	auto it = t.find(u);
	assert(it != end(t));
	t.erase(it);
}



//? Custom Helpers
template <typename T>
inline T gcd(T a, T b) { while (b != 0) swap(b, a %= b); return a; }

long long binpow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

//? __builtin_popcountll
ll GetBit(ll mask, ll bit) { return (mask >> bit) & 1LL; }
void TurnOn(ll& mask, ll bit) { mask = mask | (1LL << bit); }
void TurnOff(ll& mask, ll bit) { mask = mask & (~(1LL << bit)); }

const int dddx[8]{1, 0, -1,  0, 1,  1, -1, -1};
const int dddy[8]{0, 1,  0, -1, 1, -1,  1, -1};

using vvi = V<vi>;
using vvl = V<vl>;
using vvb = V<vb>;

const int MOD = 1e9 + 7;
const int MX = (int)2e5 + 5;
const ll BIG = 1e18;  //? not too close to LLONG_MAX
const db PI = acos((db)-1);
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};  //? for every grid problem!!
mt19937 rng(0);

int rng_int(int L, int R) { assert(L <= R);
	return uniform_int_distribution<int>(L,R)(rng);  }
ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }
//? /Custom Helpers

//? Template
//? /Template

bool brute() {
    for(ll u = 1; u < 12; u++) {
        for(ll v = 1; v < 12; v++) {
            if((u & v) == v) {
                // cout << u << " " << (u + v) << "\n";
            }
        }
    }
    return true;
}

bool brute2(ll start, ll should) {
    deque<ll> q; q.eb(start);
    // map<ll, ll> dist; dist[start] = 0;
    map<ll, ll> vis; vis[start] = true;

    while(!q.empty()) {
        auto u = q.ft; q.pop_front();
        if(u > should) continue;

        if(u == should) return true;
        // if(dist[u] > 100) continue;

        for(ll v = 1; v <= u; v++) {
            if((u & v) == v && !vis[u + v]) {
                vis[u + v] = true;
                // dist[u + v] = dist[u] + 1;
                q.eb(u + v);
            }
        }
    }
    return false;
}

bool slv(ll u, ll v) {
    if(u > v) return false;
    auto get = [&](ll x) -> vl {
        vl ans;
        for(ll bit = 0; bit <= 60LL; bit++) {
            ans.eb(bool(x & (1LL << bit)));
        }
        while(ans.bk == 0) ans.pop_back();
        return ans;
    };
    vl U = get(u);
    vl V = get(v);
    while(sz(U) < sz(V)) U.eb(0);
    reverse(all(U));
    reverse(all(V));
    const ll MAXN = sz(V);
    dbg(MAXN);

    dbg(U);
    dbg(V);
    vl pref_U = U;
    vl pref_V = V;
    for(int i = 1; i < MAXN; i++) {
        pref_U[i] += pref_U[i - 1];
        pref_V[i] += pref_V[i - 1];
    }
    auto query = [&](vl& pref, ll L, ll R) -> ll {
        ll sum = pref[R];
        if(0 <= L - 1) sum -= pref[L - 1];
        return sum;
    };
    bool ok = true;
    for(int i = 0; i < MAXN; i++) {
        if(V[i]) ok &= (query(pref_V, i, MAXN - 1) <= query(pref_U, i, MAXN - 1));
    }
    return ok;
}

void solve() {
    //? <>
    ll u, v; cin >> u >> v;
    dbg(u, v);
    bool ans = slv(u, v);
    dbg(ans);
    cout <<(ans?"YES":"NO") << "\n";
}

void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    // chk(brute());

    //? Stress Testing
    while(0) {
        RAYA;
        ll u = rng_ll(1, 1000);
        ll v = rng_ll(1, 1000);
        dbg(u, v);
        bool ans = brute2(u, v);
        bool greedy = slv(u, v);
        dbg(ans, greedy);
        chk(ans == greedy);
    }

    int t = 1; cin >> t;
    for(int i = 0; i < t; i++) {
        RAYA;
        RAYA;
        solve();
    }
    RAYA;
    RAYA;

    #ifdef LOCAL
        cerr << fixed << setprecision(5);
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
        cerr << "\033[42mtime = " << time_elapsed() << "ms\033[0m\n";
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
    #endif
}
