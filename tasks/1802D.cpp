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



// TODO: Custom Helpers
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

long long custom_abs(long long a){
    if(a < 0) a = -a;
    return a;
}
// TODO: /Custom Helpers

//? Template
/**
 * Description: 1D range minimum query. If TL is an issue, use
	* arrays instead of vectors and store values instead of indices.
 * Source: KACTL
 * Verification:
	* https://cses.fi/problemset/stats/1647/
	* http://wcipeg.com/problem/ioi1223
	* https://pastebin.com/ChpniVZL
 * Memory: O(N\log N)
 * Time: O(1)
 */

tcT> struct RMQ_Max { // floor(log_2(x))
	int level(int x) { return 31-__builtin_clz(x); }
	V<T> v; V<vi> jmp;
	int cmb(int a, int b) {
		return v[a]==v[b]?min(a,b):(v[a]>v[b]?a:b); }
	void init(const V<T>& _v) {
		v = _v; jmp = {vi(sz(v))};
		iota(all(jmp[0]),0);
		for (int j = 1; 1<<j <= sz(v); ++j) {
			jmp.pb(vi(sz(v)-(1<<j)+1));
			F0R(i,sz(jmp[j])) jmp[j][i] = cmb(jmp[j-1][i],
				jmp[j-1][i+(1<<(j-1))]);
		}
	}
	int index(int l, int r) {
		assert(l <= r); int d = level(r-l+1);
		return cmb(jmp[d][l],jmp[d][r-(1<<d)+1]); }
	T query(int l, int r) { return v[index(l,r)]; }
};

//? /Template

ll brute(ll n, vpl dpts) {
    ll ans = BIG;
    for(ll mask = 1; mask + 1 < (1LL << n); mask++) {
        ll mx_a = -BIG;
        ll mx_b = -BIG;
        for(ll i = 0; i < n; i++) {
            if(GetBit(mask, i)) ckmax(mx_a, dpts[i].f);
            else                ckmax(mx_b, dpts[i].s);
        }
        ckmin(ans, custom_abs(mx_a - mx_b));
    }
    return ans;
}

ll slv(ll n, vpl dpts) {
    dbg("Greedy");
    vpl guarda_dpts = dpts;

    auto work = [&]() -> ll {
        dbg(dpts);
        vl a(n);
        vl b(n);
        for(int i = 0; i < n; i++) {
            a[i] = dpts[i].f;
            b[i] = dpts[i].s;
        }
        RMQ_Max<ll> st_max; st_max.init(b);
        ll ans = BIG;
        set<ll> window;
        for(int i = 0; i + 1 < n; i++) {
            ll mx_left = st_max.query(i + 1, n - 1);
            ckmin(ans, custom_abs(a[i] - mx_left));
            ckmin(ans, custom_abs(a[n - 1] - b[i]));

            {
                auto it = window.lower_bound(a[i]);
                if(it != window.end() && ((*it) >= mx_left)) {
                    ckmin(ans, custom_abs(a[i] - (*it)));
                }
            }
            {
                auto it = window.lower_bound(a[i]);
                if(it != window.begin()) {
                    it--;
                    if((*it) >= mx_left) {
                        ckmin(ans, custom_abs(a[i] - (*it)));
                    }
                }
            }
            window.emplace(b[i]);
        }
        return ans;
    };
    sor(dpts);
    ll ans = work();

    dpts = guarda_dpts;
    for(auto& [a, b]: dpts) {
        swap(a, b);
    }
    sor(dpts);
    ckmin(ans, work());

    dbg("/Greedy");
    return ans;
}

void solve() {
    //? <>
    ll n; cin >> n;
    vpl dpts(n); for(auto& [a, b]: dpts) cin >> a >> b;

    ll ans = slv(n, dpts);
    dbg(ans);
    cout << ans << "\n";
}

void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    //? Stress Testing
    while(0) {
        RAYA;
        ll n = rng_ll(2, 20);
        vpl dpts(n);
        for(auto& [a, b]: dpts) {
            a = rng_ll(0, ll(1e9));
            b = rng_ll(0, ll(1e9));
        }
        dbg(n);
        dbg(dpts);
        ll ans = brute(n, dpts);
        ll greedy = slv(n, dpts);
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
