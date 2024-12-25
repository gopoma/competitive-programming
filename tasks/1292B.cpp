//* sometimes pragmas don't work, if so, just comment it!
#pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
// #pragma GCC optimize ("trapv")

#undef _GLIBCXX_DEBUG //? for Stress Testing

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

ll slv(ll x0, ll y0, ll ax, ll ay, ll bx, ll by, ll xs, ll ys, ll t) {
    auto diff = [&](ll x, ll y) -> ll {
        return (max(x, y) - min(x, y));
    };
    auto dist = [&](pl A, pl B) -> ll {
        return (diff(A.f, B.f) + diff(A.s, B.s));
    };
    vpl nodes{mp(x0, y0)};
    while(true) {
        auto [xBefore, yBefore] = nodes.bk;
        pl newNode = mp(ax * xBefore + bx, ay * yBefore + by);
        if(dist(newNode, nodes.bk) > ll(5e16)) break;
        nodes.eb(newNode);
    }
    chk(sz(nodes) <= 70);
    dbg(nodes);

    auto initialPosition = mp(xs, ys);

    ll response = 0;
    const int N = sz(nodes);
    for(int init = 0; init < N; init++) {
        ll queda = t - dist(initialPosition, nodes[init]);
        if(queda < 0) continue;

        ll guardaQueda = queda;

        {
            // from left to right
            for(int leftLimit = 0; leftLimit <= init; leftLimit++) {
                vb already(N); already[init] = true;
                queda = guardaQueda;

                ll d = dist(nodes[init], nodes[leftLimit]);
                queda -= d;
                if(queda >= 0) {
                    for(int j = leftLimit; j <= init; j++) {
                        already[j] = true;
                    }
                    for(int i = leftLimit; i + 1 < N; i++) {
                        ll d2 = dist(nodes[i], nodes[i + 1]);
                        queda -= d2;
                        if(queda >= 0) {
                            already[i + 1] = true;
                        }
                    }
                }
                ll local_response = 0;
                for(int i = 0; i < N; i++) local_response += already[i];
                ckmax(response, local_response);
            }
        }
        {
            // from right to left
            for(int rightLimit = init; rightLimit < N; rightLimit++) {
                vb already(N); already[init] = true;
                queda = guardaQueda;

                ll d = dist(nodes[init], nodes[rightLimit]);
                queda -= d;
                if(queda >= 0) {
                    for(int j = init; j <= rightLimit; j++) {
                        already[j] = true;
                    }
                    for(int i = rightLimit; i - 1 >= 0; i--) {
                        ll d2 = dist(nodes[i], nodes[i - 1]);
                        queda -= d2;
                        if(queda >= 0) {
                            already[i - 1] = true;
                        }
                    }
                }
                ll local_response = 0;
                for(int i = 0; i < N; i++) local_response += already[i];
                ckmax(response, local_response);
            }
        }
    }
    return response;
}

void solve() {
    //? <>
    ll x0, y0, ax, ay, bx, by; cin >> x0 >> y0 >> ax >> ay >> bx >> by;
    ll xs, ys, t; cin >> xs >> ys >> t;
    dbg(x0, y0, ax, ay, bx, by);
    dbg(xs, ys, t);
    ll response = slv(x0, y0, ax, ay, bx, by, xs, ys, t);
    dbg(response);
    cout << response << "\n";
}

void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    //? Stress Testing
    while(0) {
        RAYA;
        ll x0 = rng_ll(1, ll(1e16));
        ll y0 = rng_ll(1, ll(1e16));

        ll ax = rng_ll(2, ll(100));
        ll ay = rng_ll(2, ll(100));

        ll bx = rng_ll(0, ll(1e16));
        ll by = rng_ll(0, ll(1e16));

        ll xs = rng_ll(1, ll(1e16));
        ll ys = rng_ll(1, ll(1e16));
        ll t = rng_ll(1, ll(1e16));
        dbg(x0, y0, ax, bx, ay, by, xs, ys, t);
        ll greedy = slv(x0, y0, ax, ay, bx, by, xs, ys, t);
    }

    int t = 1; //! cin >> t;
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
