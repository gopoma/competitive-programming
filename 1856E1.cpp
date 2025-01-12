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
// TODO: Remind to call this.gen()
// TODO: Remind to call this.gen()
// TODO: Remind to call this.gen()
// TODO: Remind to call this.gen()
// TODO: Remind to call this.gen()
// TODO: Remind to call this.gen()
/**
 * Description: Euler Tour LCA. Compress takes a subset $S$ of nodes
 	* and computes the minimal subtree that contains all the nodes
	* pairwise LCAs and compressing edges. Returns a list of
	* \texttt{(par, orig\_index)} representing a tree rooted at 0.
	* The root points to itself.
 * Time: O(N\log N) build, O(1) LCA, O(|S|\log |S|) compress
 * Source: USACO, Simon Lindholm (KACTL)
 * Verification: USACO Debug the Bugs
 	* https://codeforces.com/contest/1320/problem/E
 */

//? #include "../../data-structures/Static Range Queries (9.1)/RMQ (9.1).h"

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

tcT> struct RMQ { // floor(log_2(x))
	int level(int x) { return 31-__builtin_clz(x); }
	V<T> v; V<vi> jmp;
	int cmb(int a, int b) {
		return v[a]==v[b]?min(a,b):(v[a]<v[b]?a:b); }
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

struct LCA {
	int N; V<vi> adj;
	vi depth, pos, par, rev; // rev is for compress
	vpi tmp; RMQ<pi> r;
	void init(int _N) { N = _N; adj.rsz(N);
		depth = pos = par = rev = vi(N); }
	void ae(int x, int y) { adj[x].pb(y), adj[y].pb(x); }
	void dfs(int x) {
		pos[x] = sz(tmp); tmp.eb(depth[x],x);
		each(y,adj[x]) if (y != par[x]) {
			depth[y] = depth[par[y]=x]+1, dfs(y);
			tmp.eb(depth[x],x); }
	}
	void gen(int R = 0) { par[R] = R; dfs(R); r.init(tmp); }
	int lca(int u, int v){
		u = pos[u], v = pos[v]; if (u > v) swap(u,v);
		return r.query(u,v).s; }
	int dist(int u, int v) {
		return depth[u]+depth[v]-2*depth[lca(u,v)]; }
	vpi compress(vi S) {
		auto cmp = [&](int a, int b) { return pos[a] < pos[b]; };
		sort(all(S),cmp); R0F(i,sz(S)-1) S.pb(lca(S[i],S[i+1]));
		sort(all(S),cmp); S.erase(unique(all(S)),end(S));
		vpi ret{{0,S[0]}}; F0R(i,sz(S)) rev[S[i]] = i;
		FOR(i,1,sz(S)) ret.eb(rev[lca(S[i-1],S[i])],S[i]);
		return ret;
	}
};
//? /Template

ll brute(ll n, vl parent) {
    LCA st; st.init(n);
    for(int i = 1; i < n; i++) st.ae(i, parent[i]);
    st.gen(0);

    auto get = [&](vl a) {
        ll cnt = 0;
        for(int u = 0; u < n; u++) {
            for(int v = 0; v < n; v++) {
                cnt += (a[u] < a[st.lca(u, v)] && a[st.lca(u, v)] < a[v]);
            }
        }
        return cnt;
    };

    vl p(n); iota(all(p), 0);

    ll mx = -BIG;
    do {
        ll local_mx = get(p);
        ckmax(mx, local_mx);
    } while(next_permutation(all(p)));
    sor(p);
    // do {
    //     ll local_mx = get(p);
    //     if(local_mx == mx) {
    //         dbg(p);
    //     }
    // } while(next_permutation(all(p)));
    return mx;
}

bitset<5005> dp;
ll slv(ll n, vl parent) {
    vvl adj(n);
    for(int i = 1; i < n; i++) {
        adj[i].eb(parent[i]);
        adj[parent[i]].eb(i);
    }
    vl subtree_size(n);
    auto dfs = [&](const auto& dfs, int u, int par) -> void {
        subtree_size[u] = 1;
        for(auto& nxt: adj[u]) {
            if(nxt == par) continue;
            dfs(dfs, nxt, u);
            subtree_size[u] += subtree_size[nxt];
        }
    }; dfs(dfs, 0, -1);
    auto dfs2 = [&](const auto& dfs2, int u, int par) -> ll {
        ll tot = 0;
        ll tot_childs = 0;
        vl subtree_sizes;

        for(auto& nxt: adj[u]) {
            if(nxt == par) continue;

            tot += subtree_size[nxt];
            subtree_sizes.eb(subtree_size[nxt]);

            tot_childs += dfs2(dfs2, nxt, u);
        }


        for(int i = 0; i <= n; i++) {
            dp[i] = 0;
        }

        dp[0] = 1;
        for(auto& x: subtree_sizes) {
            dp = dp | (dp << x);
        }

        ll mx = 0;
        for(int x = 0; x <= n; x++) {
            if(dp[x]) ckmax(mx, x * (tot - x));
        }

        ll ans = mx + tot_childs;
        return ans;
    };
    ll ans = dfs2(dfs2, 0, -1);
    return ans;
}

void solve() {
    //? <>
    ll n; cin >> n;
    vl parent(n, -1);
    for(int i = 1; i < n; i++) {
        cin >> parent[i];
        parent[i]--;
    }
    dbg(n);
    dbg(parent);
    ll ans = slv(n, parent);
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
        ll n = rng_ll(2, 9);
        vl parent(n, -1);
        for(int i = 1; i < n; i++) parent[i] = rng_ll(0, i - 1);
        dbg(n);
        dbg(parent);
        ll ans = brute(n, parent);
        ll greedy = slv(n, parent);
        dbg(ans, greedy);
        chk(ans == greedy);
    }

    while(0) {
        RAYA;
        ll n = ll(5000);
        vl parent(n, -1);
        for(int i = 1; i < n; i++) parent[i] = rng_ll(0, i - 1);
        dbg(n);
        db last = time_elapsed();
        ll greedy = slv(n, parent);
        db current = time_elapsed();
        db taken = current - last;
        dbg(taken);
        if(taken > db(2)) {
            chk(false);
        }
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
