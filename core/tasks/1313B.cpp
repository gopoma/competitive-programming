//* sometimes pragmas don't work, if so, just comment it!
// #pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
#pragma GCC optimize ("trapv")

// #undef _GLIBCXX_DEBUG //? for Stress Testing

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

pl brute(ll n, ll x, ll y) {
    if(n == 1) return mp(1, 1);

    vl A, B;
    for(ll i = 1; i <= n; i++) {
        if(i != x) A.eb(i);
        if(i != y) B.eb(i);
    }
    chk(sz(A) == n - 1);
    chk(sz(B) == n - 1);


    ll current = x + y;

    sor(A);
    vl places;

    do {
        sor(B);
        do {
            vl values;
            for(int i = 0; i < sz(A); i++) {
                values.eb(A[i] + B[i]);
            }
            ll place = 1;
            for(int i = 0; i < sz(A); i++) {
                if(values[i] <= current) {
                    place++;
                }
            }
            places.eb(place);
        } while(next_permutation(all(B)));
    } while(next_permutation(all(A)));
    sor(places);
    return mp(places.ft, places.bk);
}

pl slv2(ll n, ll x, ll y) {
    if(n == 1) return mp(1, 1);
    // mn: SUM should be x + y - 1
    ll mn = n;
    {
        // lst + adi = x + y
        ll lst = n;
        ll adi = x + y - lst + 1LL;

        auto check2 = [&](ll i) -> bool {
            return (1 <= i && i <= n);
        };

        bool inter = false;
        auto check = [&](ll middle) -> bool {
            ll clst = n   - (middle - 1LL);
            ll cadi = adi + (middle - 1LL);
            if(!check2(clst) || !check2(cadi)) return false;
            inter |= (clst <= x && x <= lst);
            inter |= (adi <= y && y <= cadi);
            return (clst + cadi > x + y);
        };

        ll left = 0;      // always good
        ll right = n + 5; // always bad
        while(left + 1 < right) {
            ll middle = fdiv(left + right, 2LL);
            if(check(middle)) left = middle;
            else right = middle;
        }
        left -= inter;
        ckmax(left, 0LL);
        mn -= left;
    }
    // mx: SUM should be x + y
    ll mx;
    {
        ll ways = min(x + y, n + 1LL) - 1LL;
        mx = ways;
    }
    return mp(mn, mx);
}

pl slv(ll n, ll x, ll y) {
    if(n == 1) return mp(1, 1);
    ll mn;
    {
        if(x == n && y == n) {
            mn = n;
        } else {
            ll left = 0;  //? always bad
            ll right = n; //? always good
            while(left + 1 < right) {
                ll middle = fdiv(left + right, 2LL);
                if(n + middle > x + y) right = middle;
                else left = middle;
            }
            mn = right;
        }
    }
    ll mx = min(x + y, n + 1LL) - 1LL;
    return mp(mn, mx);
}

void solve() {
    //? <>
    ll n, x, y; cin >> n >> x >> y;
    dbg(n, x, y);
    auto [mn, mx] = slv(n, x, y);
    dbg(mn, mx);
    cout << mn << " " << mx << "\n";
}

void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    //? Stress Testing

    if(false) {
        for(ll n = 1; n <= 7; n++) {
            for(ll x = 1; x <= n; x++) {
                for(ll y = 1; y <= n; y++) {
                    RAYA;
                    dbg(n, x, y);
                    auto [mn, mx] = brute(n, x, y);
                    auto [mn2, mx2] = slv(n, x, y);
                    dbg("Brute", mn, mx);
                    dbg("Greedy", mn2, mx2);
                    chk(mn == mn2 && mx == mx2);
                }
            }
        }
    }

    while(0) {
        RAYA;
        ll n = rng_ll(ll(1e9), ll(1e9));
        ll x = rng_ll(1, n);
        ll y = rng_ll(1, n);
        dbg(n, x, y);
        dbg(slv(n, x, y));
    }
    while(0) {
        RAYA;
        ll n = rng_ll(ll(1e9), ll(1e9));
        ll x = rng_ll(1, n);
        ll y = rng_ll(1, n);
        dbg(n, x, y);
        pl greedy1 = slv(n, x, y);
        pl greedy2 = slv2(n, x, y);
        dbg(greedy1, greedy2);
        chk(greedy1 == greedy2);
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
