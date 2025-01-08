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
/**
 * Description: sorts vertices such that if there exists an edge x->y, then x goes before y
 * Source: KACTL
 * Verification: https://open.kattis.com/problems/quantumsuperposition
 */

struct TopoSort {
	int N; vi in, res;
	V<vi> adj;
	void init(int _N) { N = _N; in.rsz(N); adj.rsz(N); }
	void ae(int x, int y) { adj[x].pb(y), ++in[y]; }
	bool sort() {
		queue<int> todo;
		F0R(i,N) if (!in[i]) todo.push(i);
		while (sz(todo)) {
			int x = todo.ft; todo.pop(); res.pb(x);
			each(i,adj[x]) if (!(--in[i])) todo.push(i);
		}
		return sz(res) == N;
	}
};
//? /Template

bool check(ll n, vl a, vl c, vl response) {
    set<ll> S; for(auto& x: response) S.emplace(x);
    chk(sz(S) == n);
    auto get = [&](vl p) -> ll {
        vb already(n);
        ll ans = 0;
        for(int i = 0; i < n; i++) {
            if(already[a[p[i]]]) ans += c[p[i]];
            else ans += 2LL * c[p[i]];
            already[p[i]] = true;
        }
        return ans;
    };

    vl p(n); iota(all(p), 0);

    ll ans = -BIG;
    do {
        ckmax(ans, get(p));
    } while(next_permutation(all(p)));
    dbg(ans, get(response));
    return (ans == get(response));
}

vl slv(ll n, vl a, vl c) {
    vvl adj(n);
    for(int u = 0; u < n; u++) {
        adj[u].eb(a[u]);
    }

    vb vis(n);
    vl stk;
    set<ll> ordered;
    vl right;
    for(int u = 0; u < n; u++) if(!vis[u]) {
        stk.clear();
        ll x = u;
        while(!vis[x]) {
            vis[x] = true;
            stk.eb(x);
            x = a[x];
        }
        int j = -1;
        for(int i = 0; i < sz(stk); i++) if(stk[i] == x) {
            j = i;
            break;
        }
        if(j == -1) continue;
        vl cyc;
        for(int i = j; i < sz(stk); i++) cyc.eb(stk[i]);
        // dbg(cyc);

        ll mn = BIG;
        ll k = -1;
        for(int i = 0; i < sz(cyc); i++) if(ckmin(mn, c[cyc[i]])) {
            k = i;
        }
        chk(k != -1);
        // dbg(k, cyc[k], c[cyc[k]]);

        vl temp;
        for(int i = 0; i < sz(cyc); i++) {
            int id = (k + i + 1) % sz(cyc);
            // dbg(id);
            temp.eb(cyc[id]);
        }
        // dbg(temp);

        for(auto& it: temp) {
            ordered.emplace(it);
            right.eb(it);
        }
    }
    vl left;
    {
        TopoSort G; G.init(n);
        for(int u = 0; u < n; u++) {
            if(!ordered.count(u) && !ordered.count(a[u])) {
                G.ae(u, a[u]);
            }
        }
        assert(G.sort());
        for(auto x: G.res) if(!ordered.count(x)) left.eb(x);
    }

    vl response;
    for(auto& it: left) response.eb(it);
    for(auto& it: right) response.eb(it);

    chk(check(n, a, c, response));

    return response;
}

void solve() {
    //? <>
    ll n; cin >> n;
    vl a(n); for(auto& x: a) {
        cin >> x;
        x--;
    }
    vl c(n); for(auto& x: c) cin >> x;
    dbg(n);
    dbg(a);
    dbg(c);

    vl response = slv(n, a, c);
    for(auto& x: response) cout << (x + 1) << " ";
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
        ll n = rng_ll(2, 5);
        vl a(n); iota(all(a), 0); for(int i = 0; i< n; i++) while(a[i] != i) a[i] = rng_ll(0, n - 1);
        vl c(n); for(auto& x: c) x = rng_ll(1, 100);
        dbg(n);
        dbg(a);
        dbg(c);
        slv(n, a, c);
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
