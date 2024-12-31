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
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

int rng_int(int L, int R) { assert(L <= R);
	return uniform_int_distribution<int>(L,R)(rng);  }
ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }
//? /Custom Helpers

//? Template
//? /Template



void solve() {
    //? <>
    ll n; cin >> n;
    vl a(n); for(auto& x: a) cin >> x;
    dbg(n);
    dbg(a);
    vl ga = a;

    vi already;
    for(int i = 0; i < n; i++) if(a[i] != -1) already.eb(i);

    if(already.empty()) {
        vl ans(n);
        for(int i = 0; i < n; i++) {
            if(i % 2 == 0) ans[i] = 1;
            else ans[i] = 2;
        }
        for(auto& x: ans) cout << x << " ";
        cout << "\n";
        return;
    }

    auto getBin = [&](ll x) -> vl {
        vl bits;
        chk((1LL << 40LL) > ll(1e8));
        for(ll bit = 0; bit < 40; bit++) {
            if(x & (1LL << bit)) bits.eb(1);
            else bits.eb(0);
        }
        while(bits.bk == 0) bits.pop_back();
        reverse(all(bits));
        return bits;
    };

    auto get = [&](ll x, ll y) -> vl {
        vl bits_x = getBin(x);
        vl bits_y = getBin(y);
        dbg(x, y, bits_x, bits_y);

        ll LongestPrefix = 0;
        for(int i = 0; i < min(sz(bits_x), sz(bits_y)); i++) {
            dbg(i, bits_x[i], bits_y[i]);
            if(bits_x[i] == bits_y[i]) {
                LongestPrefix++;
            } else break;
        }
        dbg(LongestPrefix);

        vl should;
        while(sz(bits_x) > LongestPrefix) {
            bits_x.pop_back();
            x /= 2LL;
            should.eb(x);
        }
        for(int i = LongestPrefix; i < sz(bits_y); i++) {
            if(bits_y[i] == +1) {
                x = 2LL * x + 1LL;
            } else {
                x = 2LL * x;
            }
            should.eb(x);
        }
        return should;
    };

    const int M = sz(already);
    for(int i = 0; i + 1 < M; i++) {
        RAYA;

        vl should = get(a[already[i]], a[already[i + 1]]);
        ll dist = already[i + 1] - already[i];
        dbg(dist, should);
        if(sz(should) > dist || (dist - sz(should)) % 2LL != 0LL) {
            cout << "-1\n";
            return;
        }
        for(int j = 0; j < sz(should); j++) {
            a[already[i] + j + 1] = should[j];
        }
        ll other = a[already[i + 1]] * 2LL;
        bool g = true;
        for(int j = already[i] + sz(should); j <= already[i + 1]; j++) {
            if(g) a[j] = a[already[i + 1]];
            else  a[j] = other;
            g = !g;
        }
    }

    {
        ll other = 2LL * a[already.ft];
        bool g = true;
        for(int i = already.ft; i >= 0; i--) {
            if(g) a[i] = a[already.ft];
            else  a[i] = other;
            g = !g;
        }
    }
    {
        ll other = 2LL * a[already.bk];
        bool g = true;
        for(int i = already.bk; i < n; i++) {
            if(g) a[i] = a[already.bk];
            else  a[i] = other;
            g = !g;
        }
    }

    for(int i = 0; i < n; i++) {
        chk(1LL <= a[i] && a[i] <= ll(1e9));
        if(ga[i] != -1) chk(ga[i] == a[i]);
        if(i + 1 < n) {
            chk((a[i] == a[i + 1] / 2LL) || (a[i] / 2LL == a[i + 1]));
        }
    }

    for(auto& x: a) cout << x << " ";
    cout << "\n";
}

void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    //? Stress Testing
    while(0) {
        RAYA;
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
