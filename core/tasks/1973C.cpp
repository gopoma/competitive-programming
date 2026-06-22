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
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

int rng_int(int L, int R) { assert(L <= R);
	return uniform_int_distribution<int>(L,R)(rng);  }
ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }
//? /Custom Helpers

//? Template
//? /Template

int calc(int n, vi p, vi q) {
    vi a(n); for(int i = 0; i < n; i++) a[i] = p[i] + q[i];
    int ans = 0;
    for(int i = 1; i + 1 < n; i++) {
        ans += (a[i - 1] < a[i] && a[i] > a[i + 1]);
    }
    return ans;
}

const int INF = 1e9;
pair<int, vi> brute(int n, vi p) {
    chk(4 <= n && n % 2 == 0);
    vi q(n); iota(all(q), 1);
    int ans = -INF;
    do {
        ckmax(ans, calc(n, p, q));
    } while(next_permutation(all(q)));
    sor(q);
    vi response;
    do {
        if(calc(n, p, q) == ans) {
            vi a(n); for(int i = 0; i < n; i++) a[i] = p[i] + q[i];
            //? dbg(q, a);
            
            response = q;
        }
    } while(next_permutation(all(q)));
    return mp(ans, response);
}

vi slv(int n, vi p) {
    chk(4 <= n && n % 2 == 0);
    auto get = [&](vi pos) -> pair<bool, vi> {
        vi q(n, -1);
        {
            vpi pvalues;
            each(i, pos) {
                pvalues.eb(p[i], i);
            }
            sor(pvalues);
            int mx = n;
            for(auto& [val, i]: pvalues) {
                q[i] = mx--;
            }
        }

        map<int, int> upper_bound;
        each(i, pos) {
            ckmin(upper_bound[i - 1], p[i] + q[i] - p[i - 1]);
            ckmin(upper_bound[i + 1], p[i] + q[i] - p[i + 1]);
        }
        vpi values;
        each(i, pos) {
            values.eb(p[i - 1], i - 1);
            values.eb(p[i + 1], i + 1);
        }
        remDup(values);
        sort(rall(values));
        int mn = 1;
        for(auto& [_, i]: values) {
            q[i] = mn++;
        }


        set<int> u; for(int x = 1; x <= n; x++) u.emplace(x);
        for(int i = 0; i < n; i++) {
            if(q[i] != -1) {
                safeErase(u, q[i]);
            }
        }
        for(int i = 0; i < n; i++) {
            if(q[i] == -1) {
                q[i] = *u.begin();
                safeErase(u, *u.begin());
            }
        }
        return mp(calc(n, p, q) == (n - 2) / 2, q);
    };
    vi pos, pos2;
    for(int i = 1, j = 0; i < n && j < (n - 2) / 2; i += 2, j++) {
        pos.eb(i);
    }
    for(int i = 2, j = 0; i < n && j < (n - 2) / 2; i += 2, j++) {
        pos2.eb(i);
    }
    auto [ok, q] = get(pos);
    auto [ok2, q2] = get(pos2);
    if(ok) return q;
    else if(ok2) return q2;
    else {
        dbg(n, p);
        dbg(q);
        dbg(q2);
        chk(false);
    }
}

void solve() {
    //? <>
    int n; cin >> n;
    vi p(n); each(x, p) cin >> x;
    dbg(n);
    dbg(p);
    vi ans = slv(n, p);
    dbg(ans);
    each(x, ans) cout << x << " ";
    cout << "\n";
}

void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    //? for(int n = 4; n <= 8; n += 2) {
    //?     vi p(n); iota(all(p), 1);
    //?     set<int> u;
    //?     do {
    //?         u.emplace(calc(n, p, slv(n, p)));
    //?     } while(next_permutation(all(p)));
    //?     dbg(n, u);
    //? } 

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
