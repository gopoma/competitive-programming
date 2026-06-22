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

ll get(ll x, ll y) {
    vl history{x, y};
    ll count = 0;
    while(x != 0) {
        ll z = abs(x - y);
        history.eb(z);
        x = y;
        y = z;
        count++;
    }
    dbg(count, history);
    return count;
}

ll get2(ll x, ll y) {
    ll guarda_x = x;
    ll guarda_y = y;
    chk(!(x == 0 && y == 0));

    ll count = 0;
    ll xd = 0;
    while(x != 0) {
        xd++;
        RAYA;
        { // try
            ll a = x;
            ll b = y;
            ll adi = 0;
            while(a != 0 && adi < 10) {
                ll c = abs(a - b);
                a = b;
                b = c;
                adi++;
            }
            if(a == 0) {
                count += adi;
                return count;
            }
        }

        ll d = abs(x - y);
        dbg(x, y, d);

        ll j = -1;
        {
            vl temp{x, y, d};
            ll mn = BIG;
            for(int i = 0; i < sz(temp); i++) if(ckmin(mn, temp[i])) {
                j = i;
            }
        }
        count += j;

        rep(j) {
            ll z = abs(x - y);
            x = y;
            y = z;
        }
        dbg(x, y, abs(x - y));

        vl temp2{x, y};
        rep(5) {
            temp2.eb(abs(temp2[sz(temp2) - 1] - temp2[sz(temp2) - 2]));
        }
        dbg(temp2);
        ll dist = abs(temp2[1] - temp2[4]);
        dbg(dist);

        if(temp2.ft == temp2[3]) {
            ll left = 0;        // always good
            ll right = ll(1e9);  // always bad
            while(left + 1 < right) {
                ll middle = (left + right) >> 1LL;
                if(temp2[1] - dist * middle >= temp2[0] && temp2[2] - dist * middle >= temp2[0]) left = middle;
                else right = middle;;
            }
            ll adi = 3LL * right;
            count += adi;
            x = temp2[0];
            y = temp2[1] - dist * right;
            dbg(x, y, right, count);
        } else {
            rep(5) {
                ll z = abs(x - y);
                x = y;
                y = z;
                count++;
            }
        }

        // chk(false);
    }
    chk(xd <= 50);
    return count;
}

void solve() {
    //? <>
    ll n; cin >> n;
    vl a(n); for(auto& x: a) cin >> x;
    vl b(n); for(auto& x: b) cin >> x;
    dbg(n);
    dbg(a);
    dbg(b);
    vl R;
    for(int i = 0; i < n; i++) {
        if(a[i] == 0 && b[i] == 0) continue;
        else R.eb(get2(a[i], b[i]) % 3LL);
    }
    if(R.empty()) {
        cout << "YES\n";
        return;
    }
    bool ok = true;
    ll tar = R.ft;
    for(auto& x: R) ok &= (x == tar);
    cout << (ok?"YES":"NO") << "\n";
}

void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    while(0) {
        RAYA;
        ll x = rng_ll(1, ll(1e9));
        ll y = rng_ll(1, ll(1e9));
        dbg(x, y, gcd(x, y));
        dbg("Brute");
        ll ans = get(x, y);
        dbg("/Brute");
        dbg("Greedy");
        ll greedy = get2(x, y);
        dbg("/Greedy");
        dbg(ans, greedy);
        chk(ans == greedy);
    }

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
