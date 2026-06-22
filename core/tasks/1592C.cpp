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
mt19937 rng(0);

//? Template
/**
 * Description: Generate various types of trees.
 * Source: Own + Dhruv Rohatgi
 */

////////////// DISTRIBUTIONS

// return int in [L,R] inclusive
int rng_int(int L, int R) { assert(L <= R);
	return uniform_int_distribution<int>(L,R)(rng);  }
ll rng_ll(ll L, ll R) { assert(L <= R);
	return uniform_int_distribution<ll>(L,R)(rng);  }

// return double in [L,R] inclusive
db rng_db(db L, db R) { assert(L <= R);
	return uniform_real_distribution<db>(L,R)(rng); }

// http://cplusplus.com/reference/random/geometric_distribution/geometric_distribution/
// flip a coin which is heads with probability p until you flip heads
// mean value of c is 1/p-1
int rng_geo(db p) { assert(0 < p && p <= 1); // p large -> closer to 0
	return geometric_distribution<int>(p)(rng); }

////////////// VECTORS + PERMS

// shuffle a vector
template<class T> void shuf(vector<T>& v) { shuffle(all(v),rng); }

// generate random permutation of [0,N-1]
vi randPerm(int N) { vi v(N); iota(all(v),0); shuf(v); return v; }

// random permutation of [0,N-1] with first element 0
vi randPermZero(int N) { vi v(N-1); iota(all(v),1);
	shuf(v); v.ins(bg(v),0); return v; }

// shuffle permutation of [0,N-1]
vi shufPerm(vi v) {
	int N = sz(v); vi key = randPerm(N);
	vi res(N); F0R(i,N) res[key[i]] = key[v[i]];
	return res;
}

// vector with all entries in [L,R]
vi rng_vec(int N, int L, int R) {
	vi res; F0R(_,N) res.pb(rng_int(L,R));
	return res;
}

// vector with all entries in [L,R], unique
vi rng_vec_unique(int N, int L, int R) {
	set<int> so_far; vi res;
	F0R(_,N) {
		int x; do { x = rng_int(L,R); } while (so_far.count(x));
		so_far.ins(x); res.pb(x);
	}
	return res;
}

////////////// GRAPHS

// relabel edges ed according to perm, shuffle
vpi relabelAndShuffle(vpi ed, vi perm) {
	each(t,ed) {
		t.f = perm[t.f], t.s = perm[t.s];
		if (rng()&1) swap(t.f,t.s);
	}
	shuf(ed); return ed;
}

// shuffle graph with vertices [0,N-1]
vpi shufGraph(int N, vpi ed) { // randomly swap endpoints, rearrange labels
	return relabelAndShuffle(ed,randPerm(N)); }
vpi shufGraphZero(int N, vpi ed) {
	return relabelAndShuffle(ed,randPermZero(N)); }

// shuffle tree given N-1 edges
vpi shufTree(vpi ed) { return shufGraph(sz(ed)+1,ed); }
// randomly swap endpoints, rearrange labels
vpi shufRootedTree(vpi ed) {
	return relabelAndShuffle(ed,randPermZero(sz(ed)+1)); }

void pgraphOne(int N, vpi ed) {
	//? ps(N,sz(ed));
	//? each(e,ed) ps(1+e.f,1+e.s);
}

////////////// GENERATING TREES

// for generating tall tree
pi geoEdge(int i, db p) { assert(i > 0);
	return {i,max(0,i-1-rng_geo(p))}; }

// generate edges of tree with verts [0,N-1]
// smaller back -> taller tree
vpi treeRand(int N, int back) {
	assert(N >= 1 && back >= 0); vpi ed;
	FOR(i,1,N) ed.eb(i,i-1-rng_int(0,min(back,i-1)));
	return ed; }

// generate path
vpi path(int N) { return treeRand(N,0); }

// generate tall tree (large diameter)
// the higher the p the taller the tree
vpi treeTall(int N, db p) { assert(N >= 1);
	vpi ed; FOR(i,1,N) ed.pb(geoEdge(i,p));
	return ed; }

// generate tall tree, then add rand at end
vpi treeTallShort(int N, db p) {
	assert(N >= 1); int mid = (N+1)/2;
	vpi ed = treeTall(mid,p);
	FOR(i,mid,N) ed.eb(i,rng_int(0,i-1));
	return ed; }

// lots of stuff connected to either heavy1 or heavy2
vpi treeTallHeavy(int N, db p) {
	assert(N >= 1); // + bunch of rand
	vpi ed; int heavy1 = 0, heavy2 = N/2;
	FOR(i,1,N) {
		if(i < N/4) ed.eb(i,heavy1);
		else if (i > heavy2 && i < 3*N/4) ed.eb(i,heavy2);
		else ed.pb(geoEdge(i,p));
	}
	return ed;
}

// heavy tall tree + random
// lots of verts connected to heavy1 or heavy2
vpi treeTallHeavyShort(int N, db p) {
	assert(N >= 1); // + almost-path + rand
	vpi ed; int heavy1 = 0, heavy2 = N/2;
	FOR(i,1,N) {
		if(i < N/4) ed.eb(i,heavy1);
		else if (i <= heavy2) ed.pb(geoEdge(i,p)); // tall -> heavy1
		else if (i > heavy2 && i < 3*N/4) ed.eb(i,heavy2);
		else ed.eb(i,rng_int(0,i-1));
	}
	return ed;
}

int rand_prime(int l, int r) {
	while(1) {
		int x = rng_int(l,r);
		bool bad = 0;
		for (int i = 2; i*i <= x; ++i) if (x%i == 0) bad = 1;
		if (!bad) return x;
	}
}

//? /Template

bool slv(ll n, ll k, vl a, vpl edges) {
    for(auto& x: edges) {
        x.f--; x.s--;
    }

    vvl adj(n);
    vl in(n);
    for(auto& [u, v]: edges) {
        adj[u].eb(v);
        adj[v].eb(u);

        in[u]++;
        in[v]++;
    }

    ll tot = 0;
    for(auto& x: a) tot ^= x;
    dbg(tot);

    if(tot == 0) {
        //? x ^ x = 0
        multiset<pl> ms;
        for(int u = 0; u < n; u++) ms.emplace(in[u], u);

        vl parent(n, -1);
        vb already(n);

        while(sz(ms) > 1) {
            auto it = *ms.begin(); safeErase(ms, it);
            auto [degree, node] = it;
            already[node] = true;

            if(a[node] == (tot ^ a[node])) {
                //? dbg(node + 1, a[node], tot, tot ^ a[node]);
                return true;
            } else {
                for(auto& nxt: adj[node]) {
                    if(already[nxt]) continue;
                    else {
                        parent[nxt] = node;
                        a[nxt] ^= a[node];
                        a[node] = 0;

                        auto ito = *ms.find(mp(in[nxt], nxt));
                        safeErase(ms, ito);
                        ms.emplace(--in[nxt], nxt);
                    }
                }
            }
        }
        return false;
    } else {
        //? x ^ x ^ x = 0
        if(k - 1 < 2) {
            return false;
        }

        multiset<pl> ms;
        for(int u = 0; u < n; u++) ms.emplace(in[u], u);

        const ll tar = tot;
        ll count = 0;

        vl parent(n, -1);
        vb already(n);
        while(sz(ms) > 1) {
            auto it = *ms.begin(); safeErase(ms, it);
            auto [degree, node] = it;
            already[node] = true;
            dbg(degree, node + 1);

            if(a[node] == tar) {
                count++;
                if(count == 2) {
                    return true;
                }

                tot ^= a[node];
                a[node] = 0;
            } else {
                dbg("ga");
                for(auto& nxt: adj[node]) {
                    if(already[nxt]) continue;
                    else {
                        dbg(node + 1, nxt + 1);
                        parent[nxt] = node;
                        a[nxt] ^= a[node];
                        a[node] = 0;

                        auto ito = *ms.find(mp(in[nxt], nxt));
                        safeErase(ms, ito);
                        ms.emplace(--in[nxt], nxt);
                    }
                }
            }
        }
        return false;
    }
}

void solve() {
    //? <>
    ll n, k; cin >> n >> k;
    vl a(n); for(auto& x: a) cin >> x;
    vpl edges(n - 1);
    for(auto& x: edges) {
        cin >> x.f >> x.s;
    }
    dbg(n, k);
    dbg(a);
    dbg(edges);
    bool ok = slv(n, k, a, edges);
    cout << (ok?"YES":"NO") << "\n";
}

void setIn(str s) { freopen(s.c_str(), "r", stdin); }
void setOut(str s) { freopen(s.c_str(), "w", stdout); }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

    //? Stress Testing
    while(0) {
        RAYA;
        ll n = rng_ll(2, 4);
        ll k = rng_ll(2, n);
        vl a(n); for(auto& x: a) x = rng_ll(1, 10);
        vpi _edges = treeRand(n, rng_ll(0, n + 5));
        vpl edges; for(auto& [u, v]: _edges) edges.eb(u + 1, v + 1);
        dbg(n, k);
        dbg(a);
        dbg(edges);
        slv(n, k, a, edges);
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
