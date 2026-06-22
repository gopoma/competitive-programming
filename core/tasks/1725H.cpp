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

pair<ll, str> slv(ll N, vl A) {
    vvl where(3);
    vl count(3);
    for(int i = 0; i < N; i++) {
        // dbg(i, A[i], A[i] % 3);
        where[A[i] % 3].eb(i);
        count[A[i] % 3]++;
    }
    // for(int i = 0; i < 3; i++) dbg(i, where[i], count[i]);

    str ans(N, '0');
    bool should = true;
    for(int i = 0; i < 3; i++) {
        if(count[i] >= N / 2) {
            for(int j = 0; j < N / 2; j++) {
                ans[where[i][j]] = '1';
            }
            should = false;
            break;
        }
    }

    if(should) {
        ll cnt = 0;
        for(int i = 0; i < 3; i++) {
            while(!where[i].empty() && cnt < N / 2) {
                cnt++;
                ans[where[i].bk] = '1';
                where[i].pop_back();
            }
        }
    }

    if(true) {
        vl group, group2;
        for(int i = 0; i < N; i++) {
            if(ans[i] == '1') group.eb(A[i] % 3);
            else             group2.eb(A[i] % 3);
        }
        remDup(group);
        remDup(group2);

        vb already(3);
        for(auto& x: group) {
            for(auto& y: group2) {
                already[((x + y) * (y + x) + x * y) % 3] = true;;
            }
        }
        ll cnt = 0;
        for(int i = 0; i < 3; i++) cnt += already[i];
        chk(cnt <= 2);

        {
            ll cnt = 0;
            for(auto& c: ans) cnt += (c == '1');
            chk(cnt == N / 2);
        }

        for(int i = 0; i < 3; i++) if(!already[i]) return mp(i, ans);
    }

}

void solve() {
    //? <>
    ll N; cin >> N;
    vl A(N); for(auto& x: A) cin >> x;
    auto [Z, ans] = slv(N, A);
    dbg(Z, ans);
    cout << Z   << "\n";
    cout << ans << "\n";
}

void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    if(false) {
        vpl G{
            mp(0, 0),
            mp(0, 1),
            mp(0, 2),
            mp(1, 1),
            mp(1, 2),
            mp(2, 2),
        };
        for(auto& [a, b]: G) {
            ll d = (a + b) * (b + a) + a * b;
            d %= 3;
            dbg(a, b, d);
        }
    }

    //? Stress Testing
    while(0) {
        RAYA;
        ll N = rng_ll(1, 50000);
        N *= 2LL;
        vl A(N); for(auto& x: A) x = rng_ll(1, ll(1e9));
        dbg(N);
        // dbg(A);
        slv(N, A);
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
