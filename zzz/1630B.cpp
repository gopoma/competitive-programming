//* sometimes pragmas don't work, if so, just comment it!
#pragma GCC optimize ("Ofast")
//? #pragma GCC target ("avx,avx2")
//! #pragma GCC optimize ("trapv")

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

ll brute(ll n, ll k, vl a) {
    vl gA = a;
    remDup(gA);
    const int N = sz(gA);

    auto checkRange = [&](ll x, ll y) {
        vl b(n);
        for(int i = 0; i < n; i++) {
            if(x <= a[i] && a[i] <= y) b[i] = +1;
            else b[i] = -1;
        }

        ll pref = 0;
        ll cnt = 0;
        for(int i = 0; i < n; i++) {
            if(cnt == k - 1) {
                for(int j = i; j < n; j++) {
                    pref += b[j];
                }
                return (pref > 0);
            }
            pref += b[i];
            if(pref > 0) {
                cnt++;
                pref = 0;
            }
        }
        return false;
    };

    ll dmin = BIG;
    for(int i = 0; i < N; i++) {
        for(int j = i; j < N; j++) {
            if(checkRange(gA[i], gA[j])) {
                ckmin(dmin, gA[j] - gA[i]);
            }
        }
    }
    for(int i = 0; i < N; i++) {
        for(int j = i; j < N; j++) {
            if(checkRange(gA[i], gA[j]) && (gA[j] - gA[i] == dmin)) {
                dbg(gA[i], gA[j]);
            }
        }
    }
    return dmin;
}

ll greedy = BIG;
void slv(ll n, ll k, vl a) {
    vl u = a; remDup(u);
    const int N = sz(u);

    auto checkRange = [&](ll x, ll y) {
        vl b(n);
        for(int i = 0; i < n; i++) {
            if(x <= a[i] && a[i] <= y) b[i] = +1;
            else b[i] = -1;
        }

        ll pref = 0;
        ll cnt = 0;
        for(int i = 0; i < n; i++) {
            if(cnt == k - 1) {
                for(int j = i; j < n; j++) {
                    pref += b[j];
                }
                return (pref > 0);
            }
            pref += b[i];
            if(pref > 0) {
                cnt++;
                pref = 0;
            }
        }
        return false;
    };
    auto getLeftmost = [&](ll p) -> ll {
        chk(checkRange(u[p], u[N - 1]));

        ll left = -1;     // always bad
        ll right = N - 1; // always good
        while(left + 1 < right) {
            ll middle = fdiv(left + right, 2LL);
            if(checkRange(u[p], u[middle])) right = middle;
            else left = middle;
        }

        return right;
    };
    auto getRightmost = [&](ll p) -> ll {
        chk(checkRange(u[0], u[p]));

        ll left = 0; // always good
        ll right = N; // always bad
        while(left + 1 < right) {
            ll middle = fdiv(left + right, 2LL);
            if(checkRange(u[middle], u[p])) left = middle;
            else right = middle;
        }

        return left;
    };

    ll x1 = getLeftmost(0);
    ll x2 = getRightmost(N - 1);
    // [0, x1]
    // [x2, N - 1]
    chk(checkRange(u[0], u[x1]));
    chk(checkRange(u[x2], u[N - 1]));

    ll x3 = getRightmost(x1);
    ll x4 = getLeftmost(x2);
    chk(checkRange(u[x3], u[x1]));
    chk(checkRange(u[x2], u[x4]));
    // [x3, x1]
    // [x2, x4]

    vpl options{
        mp(x3, x1),
        mp(x2, x4),
    };

    for(int delta = 1; delta < 100; delta++) {
        if(delta < N && checkRange(u[delta], u[N - 1])) {
            ll x1 = getLeftmost(delta);
            ll x3 = getRightmost(x1);
            options.eb(x3, x1);
        }
        if((N - 1) - delta >= 0 && checkRange(u[0], u[(N - 1) - delta])) {
            ll x2 = getRightmost((N - 1) - delta);
            ll x4 = getLeftmost(x2);
            options.eb(x2, x4);
        }
        if(x1 + delta < N) {
            ll x6 = x1 + delta;
            ll x5 = getRightmost(x6);
            options.eb(x5, x6);
            chk(checkRange(u[x5], u[x6]));
        }
        if(0 <= x2 - delta) {
            ll x7 = x2 - delta;
            ll x8 = getLeftmost(x7);
            options.eb(x7, x8);
            chk(checkRange(u[x7], u[x8]));
        }
    }


    using Info = tuple<ll, ll, ll>;
    Info ans = make_tuple(BIG, BIG, BIG);
    for(auto& [i, j]: options) {
        chk(u[i] <= u[j]);
        ckmin(ans, make_tuple(u[j] - u[i], u[i], u[j]));
    }
    auto [dmin, x, y] = ans;
    greedy = dmin;

    chk(checkRange(x, y));

    vi b(n);
    for(int i = 0; i < n; i++) {
        if(x <= a[i] && a[i] <= y) b[i] = +1;
        else b[i] = -1;
    }

    vpi partitions;
    int left = 0;
    int cnt = 0;
    int pref = 0;
    for(int right = 0; right < n; right++) {
        if(cnt == k - 1) {
            partitions.eb(left, n - 1);
            break;
        }
        pref += b[right];
        if(pref >= 1) {
            // dbg(left, right);
            cnt++;
            partitions.eb(left, right);
            left = right + 1;
            pref = 0;
        }
    }
    // dbg(b);
    // dbg(partitions);


    chk(sz(partitions) == k);
    for(int i = 0; i < k; i++) {
        if(i > 0) {
            auto [l, r] = partitions[i - 1];
            auto [l2, r2] = partitions[i];
            chk(r + 1 == l2);
        }
    }
    bool ok = true;
    for(auto& [i, j]: partitions) {
        vl temp;
        for(int id = i; id <= j; id++) temp.eb(a[id]);
        int pf = 0;
        for(auto& it: temp) {
            pf += (x <= it && it <= y);
        }
        ok &= (pf > 0);
    }
    chk(ok);


    // cout << x << " " << y << "\n";
    // for(auto& [i, j]: partitions) {
    //     cout << (i + 1) << " " << (j + 1) << "\n";
    // }
}

void solve() {
    //? <>
    ll n, k; cin >> n >> k;
    vl a(n); for(auto& x: a) cin >> x;
    dbg(n, k);
    dbg(a);
    slv(n, k, a);
}

void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    //? Stress Testing
    while(1) {
        RAYA;
        ll n = rng_ll(1, 2000);
        ll k = rng_ll(1, n);
        vl a(n); for(auto& x: a) x = rng_ll(1, n);

        // a = vl{2, 7, 7, 12, 4, 7, 8, 8, 13, 3, 9, 7, 1};
        // n = sz(a);
        // k = 7;

        vl gA = a; remDup(gA);
        // dbg(gA);
        // dbg("Brute");
        ll ans = brute(n, k, a);
        // dbg("/Brute");
        // dbg("Greedy");
        slv(n, k, a);
        // dbg("/Greedy");
        if(ans != greedy) {
            dbg(n, k);
            dbg(a);
            dbg(ans, greedy);
            chk(false);
        }

        // break;
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
