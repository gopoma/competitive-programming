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
//? /Template

pl brute(ll n, vl a, vl b) {
    set<pl> good;
    good.ins(mp(0, 1));
    good.ins(mp(1, 2));
    good.ins(mp(2, 0));
    vl Empty = vl(3, 0);

    map<vl, map<vl, bool>> vis;
    map<vl, map<vl, ll>> memo;
    auto dp_min = [&](const auto& dp_min, vl a, vl b) -> ll {
        if(a == Empty && b == Empty) return 0;

        if(vis[a][b]) return memo[a][b];
        vis[a][b] = true;

        ll ans = BIG;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(a[i] > 0 && b[j] > 0) {
                    vl new_a = a; new_a[i]--;
                    vl new_b = b; new_b[j]--;
                    ckmin(ans, dp_min(dp_min, new_a, new_b) + ll(good.count(mp(i, j))));
                }
            }
        }

        return memo[a][b] = ans;
    };

    map<vl, map<vl, bool>> vis2;
    map<vl, map<vl, ll>> memo2;
    auto dp_max = [&](const auto& dp_max, vl a, vl b) -> ll {
        if(a == Empty && b == Empty) return 0;

        if(vis2[a][b]) return memo2[a][b];
        vis2[a][b] = true;

        ll ans = -BIG;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(a[i] > 0 && b[j] > 0) {
                    vl new_a = a; new_a[i]--;
                    vl new_b = b; new_b[j]--;
                    ckmax(ans, dp_max(dp_max, new_a, new_b) + ll(good.count(mp(i, j))));
                }
            }
        }
        return memo2[a][b] = ans;
    };

    ll mn = dp_min(dp_min, a, b);
    ll mx = dp_max(dp_max, a, b);
    return mp(mn, mx);
}

pl slv(ll n, vl a, vl b) {
    ll mx = 0;
    {
        for(int i = 0; i < 3; i++) {
            int nxt = (i + 1) % 3;
            mx += min(a[i], b[nxt]);
        }
    }

    ll mn = BIG;
    {
        vl p(6); iota(all(p), 0);
        do {
            vl A = a;
            vl B = b;
            for(int i = 0; i < 6; i++) {
                if(p[i] < 3) {
                    ll take = min(A[p[i]], B[p[i]]);
                    A[p[i]] -= take;
                    B[p[i]] -= take;
                } else {
                    int j = p[i] - 3;
                    int nxt = (j + 1) % 3;
                    ll take = min(A[nxt], B[j]);
                    A[nxt] -= take;
                    B[j] -= take;
                }
            }
            ll local_mn = 0;
            for(int i = 0; i < 3; i++) {
                int nxt = (i + 1) % 3;
                local_mn += min(A[i], B[nxt]);
            }
            // dbg(local_mn, A, B);
            ckmin(mn, local_mn);
        } while(next_permutation(all(p)));
    }
    return mp(mn, mx);
}

void solve() {
    //? <>
    ll n; cin >> n;
    vl a(3), b(3);
    for(auto& x: a) cin >> x;
    for(auto& x: b) cin >> x;

    auto [mn, mx] = slv(n, a, b);
    cout << mn << " " << mx << "\n";
}

void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    //? Stress Testing
    while(0) {
        RAYA;
        ll n = rng_ll(1, 30);
        auto get = [&]() {
            vl ans(3);
            ll sum = 0;
            for(auto& x: ans) {
                x = rng_ll(0, n - sum);
                sum += x;
            }
            ans.bk = n - ans[0] - ans[1];
            return ans;
        };
        vl a = get();
        vl b = get();
        dbg(n);
        dbg(a);
        dbg(b);
        auto ans = brute(n, a, b);
        auto greedy = slv(n, a, b);
        dbg(ans, greedy);
        chk(ans == greedy);
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
