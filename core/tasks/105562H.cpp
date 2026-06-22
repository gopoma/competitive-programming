// #pragma GCC optimize ("Ofast")
#include <bits/stdc++.h>
using namespace std;



#ifdef LOCAL
    #include "helpers/debug.h"
    #define GA dbg(0);
#else
    #define dbg(...)     0
    #define chk(...)     0
    #define GA 0;

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



//? Template
const int MOD = 998244353;
// const int MOD = 1e9 + 7;
const int MX = (int)2e5 + 5;
const ll BIG = 1e18;  //? not too close to LLONG_MAX
const ll INF = 1e18;
const db PI = acos((db)-1);
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1};  //? for every grid problem!!
mt19937 rng(0);

// bits
ll GetBit(ll mask, ll bit) { return (mask >> bit) & 1LL; }
void TurnOn(ll& mask, ll bit) { mask = mask | (1LL << bit); }
void TurnOff(ll& mask, ll bit) { mask = mask & (~(1LL << bit)); }

//? Generator
int rng_int(int L, int R) {
    assert(L <= R);
    return uniform_int_distribution<int>(L, R)(rng);
}
ll rng_ll(ll L, ll R) {
    assert(L <= R);
    return uniform_int_distribution<ll>(L, R)(rng);
}
//? /Generator

#define lb lower_bound
#define ub upper_bound
tcT > int lwb(V<T>& a, const T& b) { return int(lb(all(a), b) - bg(a)); }
tcT > int upb(V<T>& a, const T& b) { return int(ub(all(a), b) - bg(a)); }

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

const int MAXN = 2e5 + 5;
const int MAXD = 30;  // ceil(log2(10^9))

int parent[MAXN][MAXD];
int jump(int a, int d) {
	for (int i = 0; i < MAXD; i++)
		if (d & (1 << i)) a = parent[a][i];
	return a;
}

void slv(ll n, vl nxt, bool isDebugging) {
    if(isDebugging) {
        for (int d = 1; d < MAXD; d++) {
		    for (int i = 1; i <= n; i++) {
			    parent[i][d] = 0;
		    }
        }

        for (int i = 1; i <= n; i++) { parent[i][0] = nxt[i - 1]; }
        // Evaluate the parent matrix
	    for (int d = 1; d < MAXD; d++) {
		    for (int i = 1; i <= n; i++) {
			    parent[i][d] = parent[parent[i][d - 1]][d - 1];
		    }
        }
    }

    ll tot_queries = 0;
    auto mq = [&](ll c, ll r) -> ll {
        // dbg(c, r);

        tot_queries++;
        chk(tot_queries <= 1000);

        if(isDebugging) {
            return jump(r, c);
        } else {
            cout << "? " << c << " " << r << endl;
            ll res;
            cin >> res;
            return res;
        }
    };

    auto answer = [&](ll c, ll r) -> void {
        // dbg(c, r);
        if(isDebugging) {
            chk(tot_queries <= 1000);
            chk(jump(r, c) == c);
            dbg("ok");
        } else {
            cout << "! " << c << " " << r << endl;
        }
    };



    ll cur = mq(n, 1);
    ll fir = cur;

    vl order;
    order.push_back(cur);
    set<ll> already;
    already.insert(cur);

    rep (449) {
        ll ne = mq(1, cur);
        if (already.count(ne)) {
            ll m = sz(order);

            ll xd = fir % m;
            ll ask = m - xd;

            ll gaaaaa = mq(ask, fir);
            cout << "! " << fir << " " << gaaaaa << endl;
            return;
        } else {
            order.push_back(ne);
            already.insert(ne);
            cur = ne;
        }
    }

    ll dist = 0;
    do {
        dist += 450;
        cur = mq(450, cur);
    } while(already.count(cur));

    ll ind = 0;
    ll z = sz(order);
    for (int i = 0; i < z; ++i) {
        if (order[i] == cur) ind = i;
    }
    dist -= ind;

    ll m = dist;

    ll xd = fir % m;
    ll ask = m - xd;

    ll gaaaaa = mq(ask, fir);

    answer(fir, gaaaaa);
}

void solve() {
    ll n;
    cin >> n;

    slv(n, vl(), false);
}

void setIn(str s) { freopen(s.c_str(), "r", stdin); }
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    while(1) {
        RAYA;
        ll n = ll(1e5);
        // vl nxt(n); for(auto& x: nxt) x = rng_ll(1, n);
        vl nxt(n);
        for(int i = 0; i < n - 1; i++) {
            nxt[i] = i + 2;
        }
        nxt.bk = 1;
        dbg(n);
        // dbg(nxt);
        slv(n, nxt, true);
    }

    //setIn("input.txt");
    int t = 1;
    // cin >> t;
    for(int i = 0; i < t; i++) {
        RAYA;
        RAYA;
        solve();
    }

    #ifndef LOCAL
        cout << endl;
    #endif
    RAYA;
    RAYA;

    #ifdef LOCAL
        cerr << fixed << setprecision(5);
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
        cerr << "\033[42mtime = " << time_elapsed() << "ms\033[0m\n";
        cerr << "\033[42m++++++++++++++++++++\033[0m\n";
    #endif
}
