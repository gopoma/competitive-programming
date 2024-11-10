//* sometimes pragmas don't work, if so, just comment it!
//? #pragma GCC optimize ("Ofast")
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
    ll n, m, v; cin >> n >> m >> v;
    vl a(n); each(x, a) cin >> x;
    dbg(n, m, v);
    dbg(a);

    auto get_pref_dp = [&](vl A) -> vl {
        const int N = sz(A);
        vl pref = A;
        for(int i = 1; i < N; i++) pref[i] += pref[i - 1];
        pref.insert(pref.begin(), 0);
        vl dp(N + 1);
        for(int i = 1; i <= N; i++) {
            ll need = pref[i] - v;
            if(need < pref.ft) {
                dp[i] = 0;
            } else {
                int j = upper_bound(all(pref), need) - pref.begin();
                j--;
                dp[i] = dp[j] + 1;
            }
        }
        vl response;
        for(int i = 1; i <= N; i++) response.eb(dp[i]);
        return response;
    };

    vl dp_pref = get_pref_dp(a);
    reverse(all(a));
    vl dp_suff = get_pref_dp(a);
    reverse(all(a));
    reverse(all(dp_suff));
    dbg(dp_pref);
    dbg(dp_suff);

    vl pref = a;
    for(int i = 1; i < n; i++) pref[i] += pref[i - 1];
    auto query = [&](int L, int R) -> ll {
        ll sum = pref[R];
        if(0 <= L - 1) sum -= pref[L - 1];
        return sum;
    };

    ll ans = -BIG;
    if(dp_pref.bk >= m || dp_suff.ft >= m) ans = 0;
    for(ll i = 0; i < n; i++) {
        RAYA;
        const ll llevaCuantosPref = ((0 <= i - 1)? dp_pref[i - 1] : 0LL);
        const ll fixedLeft = i;

        ll llevaCuantosSuffHastaAhora = 0;
        if(fixedLeft + 1 < n) llevaCuantosSuffHastaAhora = dp_suff[fixedLeft + 1];
        if(llevaCuantosPref + 1LL + llevaCuantosSuffHastaAhora >= m + 1) {
            dbg(i, "good", fixedLeft);
            auto check = [&](ll middle) -> bool {
                ll adi = 0;
                if(middle + 1 < n) adi = dp_suff[middle + 1];
                ll sumita = llevaCuantosPref + 1LL + adi;
                return (sumita >= m + 1);
            };
            ll left = fixedLeft; //? always good
            ll right = n; //? always bad
            while(left + 1 < right) {
                ll middle = fdiv(left + right, 2LL);
                if(check(middle)) left = middle;
                else right = middle;
            }
            ll until = left;
            ckmax(ans, query(fixedLeft, until));
        }
    }
    if(ans < 0) cout << "-1\n";
    else cout << ans << "\n";
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
